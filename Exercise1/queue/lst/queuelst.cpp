
namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& que){
    List<Data>::operator=(que);
    return *this;
}

template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>&& que) noexcept{
    List<Data>::operator=(std::move(que));
    return *this;
}

template <typename Data>
inline bool QueueLst<Data>::operator==(const QueueLst<Data>& que) const noexcept{
    return List<Data>::operator==(que);
}

template <typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& que) const noexcept{
    return !(*this == que);
}

template <typename Data>
const Data& QueueLst<Data>::Head() const{
    if(!List<Data>::Empty()){
        return List<Data>::Front();
    }

    throw std::length_error("Trying to access the head of an empty queue");
} 

template <typename Data>
Data& QueueLst<Data>::Head(){
    if(!List<Data>::Empty()){
        return List<Data>::Front();
    }

    throw std::length_error("Trying to access the head of an empty queue");
}

template <typename Data>
void QueueLst<Data>::Dequeue(){
    if(!List<Data>::Empty())
        List<Data>::RemoveFromFront();
    else
        throw std::length_error("Trying to dequeue from an empty queue");
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue(){
    if(!List<Data>::Empty())
        return List<Data>::FrontNRemove();

    throw std::length_error("Trying to dequeue from an empty queue");
}

template <typename Data>
void QueueLst<Data>::Enqueue(const Data& d){
    List<Data>::InsertAtBack(d);
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data&& d){
    List<Data>::InsertAtBack(std::move(d));
}
/* ************************************************************************** */

}
