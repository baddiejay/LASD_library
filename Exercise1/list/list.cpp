
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
inline ~Node(){
  delete next;
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
List<Data>::List(const MappableContainer<Data>& mc){
  //Viene usata la map di cui sto facendo override o la map precedente?
  size = mc.Size();
  List l = new list[size];
  unsigned long i = 0;
  
  mc.Map([this, &i] (const Data& data) {l->element = data;});
}

template <typename Data>
List<Data>::List(MutableMappableContainer<Data>&&) noexcept{
  size = mmc.Size();
  List l = new List[size];
  unsigned long i = 0;
  
  mmc.Map([this, &i] (const Data& data) {elements = std::move(data)});
}

//Copy constructor
template <typename Data>
List<Data>::List(const List<Data>& l){
  Node* tmp = l.head;
  while(tmp != nullptr){
    InsertAtBack(tmp->element);
    tmp = tmp-next;
  }
}

//Move constructor
template <typename Data>
List<Data>::List(List<Data> && l) noexcept{
  //Cambio solo i puntatori, tanto con next so arrivare agli altri
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
  //Crep una nuova lista usando il costruttore di copia
  List<Data>* tmp = new List<Data>(l),
} 

// Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& l) noexcept{
  
}
  
template <typename Data>
bool List<Data>::operator==(const List<Data>& l) const noexcept{
  if(size != l.size)
    return false;
  //Devo scorrere le due liste in maniera parallela e confrontare gli elementi
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
void List<Data>::Clear(){
  if(size > 0){
    while(head != nullptr){
      Node * tmp = head;
      head = head -> next;
      delete tmp;
     }
  }
  
  head = nullptr;
  tail = nullptr;
  size = 0;
}

/* ************************************************************************** */

}
