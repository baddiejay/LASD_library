
namespace lasd {

/* ************************************************************************** */
template <typename Data>
const Data& StackLst<Data>::Top() const{
    if(List<Data>::size != 0){
        return List<Data>::Front();
    }

    throw std::lenght_error("Trying to access the top of an empty stack")
}

template <typename Data>
StackLst<Data>::Data& Top(){
    if(List<Data>::size != 0){
        return List<Data>::Front();
    }

    throw std::lenght_error("Trying to access the top of an empty stack")
}

template <typename Data>
void StackLst<Data>::Pop(){
    if(List<Data>::size != 0)
        List<Data>::RemoveFromFront();

    throw std::lenght_error("Trying to pop from an empty stack")
}

template <typename Data>
Data StackLst<Data>::TopNPop(){
    if(List<Data>::size != 0)
        return List<Data>::FrontNRemove();

    throw std::lenght_error("Trying to pop from an empty stack")
}

template <typename Data>
void StackLst<Data>::Push(const Data& d){
    List<Data>::InsertAtFront(d)
}

template <typename Data>
void StackLst<Data>::Push(Data&& d){
    List<Data>::InsertAtFront(d)
}

/* ************************************************************************** */

}
