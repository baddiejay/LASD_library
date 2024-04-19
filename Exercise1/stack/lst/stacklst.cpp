
namespace lasd {

/* ************************************************************************** */

//The assignment operator needs to return *this
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& st){
    List<Data>::operator=(st);
    return *this;
}

template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& st) noexcept{
    List<Data>::operator=(std::move(st));
    return *this;
}

template <typename Data>
inline bool StackLst<Data>::operator==(const StackLst<Data>& st) const noexcept{
    return List<Data>::operator==(st);
}

template <typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data>& st) const noexcept{
    return !(*this == st);
}

template <typename Data>
const Data& StackLst<Data>::Top() const{
    if(List<Data>::size != 0){
        return List<Data>::Front();
    }
    throw std::length_error("Trying to access the top of an empty stack");

}

template <typename Data>
Data& StackLst<Data>::Top(){
    if(List<Data>::size != 0){
        return List<Data>::Front();
    }
    throw std::length_error("Trying to access the top of an empty stack");
}

template <typename Data>
void StackLst<Data>::Pop(){
    if(List<Data>::size != 0)
        List<Data>::RemoveFromFront();
    else
    	throw std::length_error("Trying to pop from an empty stack");
}

template <typename Data>
Data StackLst<Data>::TopNPop(){
    if(List<Data>::size != 0)
        return List<Data>::FrontNRemove();
    throw std::length_error("Trying to pop from an empty stack");
}

template <typename Data>
void StackLst<Data>::Push(const Data& d){
    List<Data>::InsertAtFront(d);
}

template <typename Data>
void StackLst<Data>::Push(Data&& d) noexcept{
    List<Data>::InsertAtFront(std::move(d));
}

/* ************************************************************************** */

}
