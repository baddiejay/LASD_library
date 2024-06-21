
namespace lasd {

/* ************************************************************************** */
//Constructor given the data 
template <typename Data>
inline List<Data>::Node::Node(Data&& data) noexcept{
  std::swap(element, data);
  next = nullptr;
}

//Constructor given another Node COPY
template <typename Data>
inline List<Data>::Node::Node(const Node& node){
  element = node.element;
  next = node.next;
}

//Constructor given another Node MOVE
template <typename Data>
inline List<Data>::Node::Node(Node&& node) noexcept{
  std::swap(element, node.element);
  std::swap(next, node.next);
}

template <typename Data>
List<Data>::Node::~Node(){
     delete next;
}

template <typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept{
  return (element == node.element) && ((next == nullptr && node.next == nullptr) || ((next != nullptr && node.next != nullptr) && (*next = *node.next)));
}

template <typename Data>
bool inline List<Data>::Node::operator!=(const Node& node) const noexcept{
  return !((*this) == node);
}

// ******************** LIST ************************

template<typename Data>
List<Data>::List(const TraversableContainer<Data> & con){
    con.Traverse(
      [this](const Data& newData){
        InsertAtBack(newData);
        }
    );
}

template<typename Data>
List<Data>::List(MappableContainer<Data> && con){
    con.Map(
      [this] (Data& newData){
        InsertAtBack(std::move(newData));
        }
    );
}

template<typename Data>
List<Data>::List(const List<Data>& l){
    // Initialise destination list as empty
    head = nullptr;
    size = 0;

    // Copy elements from the source list only if it is not empty
    if(l.size != 0){
        Node* tmp = l.head;
        while(tmp != nullptr){
            InsertAtBack(tmp->element);
            tmp = tmp->next;
        }
    }
}

template<typename Data>
List<Data>::List(List && l) noexcept{
  //Swapping only head and tail because using the next I can access all the values in between
  std::swap(head, l.head);
  std::swap(tail, l.tail);
  std::swap(size, l.size);
}

template<typename Data>
List<Data>::~List(){
    delete head; 
}

template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& l){
  //COPY AND SWAP IDIOM
  if (this != &l) { // Self-assignment control
    List<Data> tmp(l); // Use the copy constructor to create a copy of l
    std::swap(*this, tmp); // Swap all current object with tmp
  }
  return *this;
} 

template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& l) noexcept{
  std::swap(head, l.head);
  std::swap(tail, l.tail);
  std::swap(size, l.size);
  return *this;
}

template <typename Data>
bool List<Data>::operator==(const List<Data>& l) const noexcept{
  if(size != l.size)
    return false;
  //Traversing the two lists at the same time and comparing each element
  Node* tmp_1 = head;
  Node* tmp_2 = l.head;

  while(tmp_1 != nullptr){
    if(tmp_1->element != tmp_2->element)
      return false;
    tmp_1 = tmp_1->next;
    tmp_2 = tmp_2->next;
  }
  return true;
}

template <typename Data> 
bool List<Data>::operator!=(const List<Data>& l) const noexcept{
  return !(*this == l);
}

template <typename Data>
void List<Data>::InsertAtFront(const Data& data){
  Node* tmp = new Node(data);
  tmp->next = head;
  head = tmp;
  //In case it is the first item in the list, it's the head but also the tail
  if(tail == nullptr){
    tail = head;
  }
  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& data){
  //Before data had its own memory buffer, now the compiler allows another object to own it
  Node* tmp = new Node(std::move(data));
  tmp->next = head;
  head = tmp;
  if(tail == nullptr){
    tail = head;
  }
  size++;
}

template <typename Data>
void List<Data>::RemoveFromFront(){
    if(head != nullptr){
        Node * front = head;          // Save the address of the head I want to delete
        if(tail == head){
            head = tail = nullptr;    // If I have only one node the list returns empty
        } else {
            head = head->next;        // Otherwise place your head forward
        }
        size--;  
        front->next = nullptr;        // Detach the next one to avoid recursive deletion
        delete front;
    } else {
        throw std::length_error("Trying to access an empty list");
    }
}

template <typename Data>
Data List<Data>::FrontNRemove(){
    if(head != nullptr){
        Node * front = head;
        if(tail == head){
            head = tail = nullptr;
        } else {
            head = head->next;
        }
        size--;
        front->next = nullptr;
        Data dat(std::move(front->element));
        delete front;
        return dat;
    } else {
        throw std::length_error("Trying to access an empty list");
    }
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& data){
  Node* tmp = new Node(data);

  if(tail == nullptr){
    head = tmp;        // If the tail is empty, it means that it is the first element I am inserting and I also update the head
  } else{
    tail->next = tmp;  // Otherwise, I attach the node I created to the next of the current tail
  }
  tail = tmp;          //I update the new tail
  size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& data){
    Node* tmp = new Node(std::move(data));

  if(tail == nullptr){
    head = tmp;
  } else{
    tail->next = tmp;
  }
  tail = tmp;
  size++;
}

template <typename Data>
void List<Data>::Clear(){
    delete head;
    head = tail = nullptr;
    size = 0;
}

template <typename Data>
bool List<Data>::Insert(const Data& data){
  //If the element is already inside I don't add it because I don't want duplicates
  for(Node * curr = head; curr != nullptr; curr = curr->next){
    if(curr->element == data){
        return false;
    }
  } 
  InsertAtBack(data);
  return true;
}

template <typename Data>
bool List<Data>::Insert(Data&& data){
  //If the element is already inside I don't add it because I don't want duplicates
  for(Node * curr = head; curr != nullptr; curr = curr->next){
    if(curr->element == data){
        return false;
    }
  } 
  InsertAtBack(std::move(data));
  return true;
}

//Remove one node but keeps the connection with his next
template <typename Data>
bool List<Data>::Remove(const Data& data){
    if (size == 0) {
        return false;
    } else if (head->element == data) {
        RemoveFromFront();
        return true;
    } else {
        Node * tmpNode1 = head;            // I always keep the reference to the previous node
        Node * tmpNode2 = head->next;

        while (tmpNode2 != nullptr) {
        if (tmpNode2->element == data) {
            //When I've found the one i want to delete i connect the previous with the next 
            tmpNode1->next = tmpNode2->next;
            tmpNode2->next = nullptr;
            delete tmpNode2;
            size--;
            //If the next one I hook is nullptr then I set my tail to tmp1 which is the last node in my list
            if (tmpNode1->next == nullptr){
                tail=tmpNode1;
            }
            return true;
            //tmpNode2->next ? tmpNode2->next = nullptr : tail = tmpNode1;
        }
        tmpNode1 = tmpNode2;
        tmpNode2 = tmpNode2->next;
        }

        return false;
   }
}

// Must necessarily scroll through the list, it will be just as costly as moving the element away from the list
template <typename Data>
const Data& List<Data>::operator[](const unsigned long index) const{
  if (index < size) {
    Node *temp = head;
    for (unsigned long i=0; i<index; i++){
      temp = temp->next;
    }
    return temp->element;
  } else {
    throw std::out_of_range("Acess at index " + std::to_string(index) + "; List size: " + std::to_string(size));
  }
}

template <typename Data>
Data& List<Data>::operator[](const unsigned long index){
   if (index < size) {
    Node *temp = head;
    for (unsigned long i=0; i<index; i++){
      temp = temp->next;
    }
    return temp->element;
  } else {
    throw std::out_of_range("Acess at index " + std::to_string(index) + "; List size: " + std::to_string(size));
  }
}

template <typename Data>
const Data& List<Data>::Front() const{
  if(size != 0){
    return head->element;
  } else {
    throw std::length_error("Acces to an empty List");
  }
}

template <typename Data>
Data& List<Data>::Front(){
  if(size != 0){
    return head->element;
  } else {
    throw std::length_error("Acces to an empty List");
  }
}

//Back using operator[] would require a time linear to the input. To be more efficent I use the tail pointer 
template <typename Data>
const Data& List<Data>::Back() const {
  if(size != 0){
    return tail->element;
  } else {
    throw std::length_error("Acces to an empty List");
  }
}

template <typename Data>
Data& List<Data>::Back(){
 if(size != 0){
    return tail->element;
 } else {
    throw std::length_error("Acces to an empty List");
 }
}

template <typename Data>
void List<Data>::Traverse(TraverseFun fun) const{
    PreOrderTraverse(fun, head);
}

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun) const{
    PreOrderTraverse(fun, head);
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun) const{
    PostOrderTraverse(fun, head);
}

template <typename Data>
void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun) {
   PreOrderMap(fun, head);
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun) {
   PostOrderMap(fun, head);
}


//********************* AUXILIARY FUNCTIONS ************************
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node* cur) const{
    for(; cur!=nullptr; cur=cur->next){  //cur already initialized when passed as a parameter
    	if(cur != nullptr){ // Checks whether the current node is non-null before accessing its data (invalid access)
            fun(cur->element);
        }
    }
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node* cur) const{
    if (cur!=nullptr){
      //Recursive call until i reach the end
      PostOrderTraverse(fun, cur->next);
      fun(cur->element);
    }
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node * cur) {
  for (; cur!=nullptr; cur=cur->next){
    if(cur != nullptr){ // Checks whether the current node is non-null before accessing its data (invalid access)
            fun(cur->element);
    }
  }
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node * cur) {
  if (cur!=nullptr){
    PostOrderMap(fun, cur->next);
    fun(cur->element);
  }
}
/* ************************************************************************** */

}
