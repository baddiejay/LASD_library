
namespace lasd {

/* ************************************************************************** */

//-----------------------NODE-----------------------------
template <typename Data>
//Constructor given the data 
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
bool List<Data>::Node::operator==(const Node& node) const noexcept{
  return (element == node.element) && ((next == nullptr && node.next == nullptr) || ((next != nullptr && node.next != nullptr) && (*next = *node.next)));
}

bool inline List<Data>::Node::operator!=(const Node& node) const noexcept{
  return !(this == node);
}

//-----------------------LIST-----------------------------

template <typename Data>
inline List<Data>::List(const MappableContainer<Data>& mc){
  container.Map([this] (const Data& newData){
      InsertAtBack(newData);
    })
}

template <typename Data>
inline List<Data>::List(MutableMappableContainer<Data>&&) noexcept{
  container.Map([this] (Data& newData){
      InsertAtBack(std::move(newData));
    });;
}

//Copy constructor
template <typename Data>
List<Data>::List(const List<Data>& l){
  if(l.size != 0){
    Node* tmp = l.head;
    while(tmp != nullptr){
      InsertAtBack(tmp->element);
      tmp = tmp->next;
    }

    //Since I don't have any reference to tmp outside the function, I have to delete here
    delete tmp;
    tmp = nullptr;
  }
}

//Move constructor
template <typename Data>
List<Data>::List(List<Data> && l) noexcept{
  //Swapping only head and tail because using the next I can access all the values in between
  std::swap(head, l.head);
  std::swap(tail, l.tail);
  std::swap(size, l.size);
}

template <typename Data>
List<Data>::~List(){
  Clear();
}

// Copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& l){
  //Building a new list using the copy constructor. Copy and swap idiom
  List<Data>* tmp = new List<Data>(l);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
} 

// Move assignment
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
void List<Data>::InsertAtFront(const Data& data) noexcept{
  Node* tmp = new Node(data);
  //If head is empty, I insert in head
  if(head == nullptr){
    head = tmp;
    tail = head;
  }
  else {
    tmp->next = head;
    head = tmp;
  }

  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& data) noexcept{
  //Before data had its own memory buffer, now the compiler allows another object to own it
  Node* tmp = new Node(std::move(data));
  if(head == nullptr){
    head = tmp;
    tail = head;
  }
  else {
    //The tail doesn't move since I'm inserting at front
    tmp->next = head;
    head = tmp;
  }

  size++; 
}

template <typename Data>
void List<Data>::RemoveFromFront(){
  if(size != 0){
    Node* tmp = head;
    head = head -> next;
    size--;
    delete tmp;
    tmp = nullptr;

    if(size == 0){
        head=nullptr;
        tail=nullptr;
    }
  }
  else 
    throw std::lenght_error("Trying to access an empty list");
  
}

template <typename Data>
Data List<Data>::FrontNRemove(){
  if(size != 0){
    Node* tmp = head;
    head = head -> next;
    size--;
    Data returnValue = tmp->element;
    delete tmp;
    tmp = nullptr;

    if(size == 0){
        head=nullptr;
        tail=nullptr;
    }

    return returnValue;
  }
  /*OR 
  
        Data frontData = Front();
        
        RemoveFromFront();

        return frontData;
  
  */
  throw std::lenght_error("Trying to access an empty list");
}

template <typename Data>
void InsertAtBack(const Data& data){
  Node* tmp = new Node(data);
  if(head == nullptr){
    head = tmp;
    tail = tmp;
  }
  else{
    tail->next = tmp;
    tail = tmp;
  }

  size++;
}

template <typename Data>
void InsertAtBack(Data&& data) noexcept{
  Node* tmp = new Node(std::move(data));
  if(head == nullptr){
    head = tmp;
    tail = tmp;
  }
  else{
    tail->next = tmp;
    tail = tmp;
  }

  size++;
}

template <typename Data>
void List<Data>::Clear(){
  if(size > 0){
    Node * tmp = new Node();
    while(head != nullptr){
      tmp = head;
      head = head -> next;
      delete tmp;
     }
  }
  
  delete head;
  delete tail;

  head = nullptr;
  tail = nullptr;
  tmp = nullptr;
  size = 0;

  /*OR
  ulong currSize = Size();

    for(ulong i = 0; i < currSize; i++) {
      RemoveFromFront();
    }

    head = nullptr;
    tail = nullptr;

    size = 0;
  */
}

template <typename Data>
bool List<Data>::Insert(const Data& data) override{
  //If the element is already inside I don't add it because I don't want duplicates
  if (FoldableContainer<Data>::Exists(element)){
    return false;

  } else {
    InsertAtBack(element);
    return true;
  }
}

template <typename Data>
bool List<Data>::Insert(Data&& data) noexcept override{
  Data tmpData = std::move(data);
    
    if (FoldableContainer<Data>::Exists(tmpData)) 
      return false;
    else {
      InsertAtBack(std::move(tmpData));
      return true;
    } 
}

//Remove one node but keeps the connection with his next
template <typename Data>
bool List<Data>::Remove(const Data& data) override{
  if (head == nullptr) {
    return false;
  } else if (head->data == data) {
    RemoveFromFront();
    return true;
  } else {
    Node * tmpNode1 = head;
    Node * tmpNode2 = head->next;

    while (tmpNode2 != nullptr) {
      if (tmpNode2->data == data) {
        //When I've found the one i want to delete i connect the previous with the next 
        tmpNode1->next = tmpNode2->next;
        delete tmpNode2;
        tmpNode2 = nullptr;
        size--;
        if (tmpNode1->next == nullptr)
          tail=tmpNode1;
        return true;
      }

      tmpNode1 = tmpNode2;
      tmpNode2 = tmpNode2->next;
    }
    return false;
  }
}

template <typename Data>
const Data& List<Data>::operator[](const ulong index) const override{
  if (index < size) {
    Node *temp = head;

    for (ulong i=0; i<index; i++)
      temp = temp->next;
    
    return temp->data;
  } 

  throw std::out_of_range("Acess at index " + std::to_string(index) + "; List size: " + std::to_string(size));;
}

template <typename Data>
Data& List<Data>::operator[](const ulong index) override{
   if (index < size) {
    Node *temp = head;

    for (ulong i=0; i<index; i++)
      temp = temp->next;

    return temp->data;
  } 
  
  throw std::out_of_range("Acess at index " + std::to_string(index) + "; List size: " + std::to_string(size));
}

template <typename Data>
const Data& List<Data>::Front() const override{
  if(size != 0)
    return head->element;
  
  throw std::length_error("Acces to an empty List");
}

template <typename Data>
Data& List<Data>::Front() override{
  if(size != 0)
    return head->element;
  
  throw std::length_error("Acces to an empty List");
}

template <typename Data>
const Data& List<Data>::Back() const override{
  if(size != 0)
    return tail->element;
  
  throw std::length_error("Acces to an empty List");
}

template <typename Data>
Data& List<Data>::Back() override{
 if(size != 0)
    return tail->element;
  
 throw std::length_error("Acces to an empty List");
}

/* ************************************************************************** */

}
