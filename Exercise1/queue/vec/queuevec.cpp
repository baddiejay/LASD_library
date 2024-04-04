
namespace lasd {

/* ************************************************************************** */
template <typename Data>
QueueVec<Data>::QueueVec(const MappableContainer<Data>& mc) : Vector<Data>(mc){
    head = 0;
    tail = mc.size-1;
}

template <typename Data>
QueueVec<Data>::QueueVec(const MutableMappableContainer<Data>&& mmc) : Vector<Data>(std::(mmc)){
    head = 0;
    tail = mc.size-1;
}

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& cpy) : Vector<Data>(cpy){
    head = cpy.head;
    tail = cpy.tail;
}

template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& mov) noexcept Vector<Data>(std::(mov)){
    std::swap(head, mov.head);
    std::swap(tail, mov.tail);
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& que){
    Vector<Data>::operator=(que);
    head = que.head;
    tail = que.tail;
    return *this;
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& que) noexcept{
    Vector<Data>::operator=(std::move(que));
    std::swap(head, que.head);
    std::swap(tail, que.tail);
    return *this;
}

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& que) const noexcept{
    if(Size() != que.Size())
        return false;
    
    unsigned long i = head;
    unsigned long k = que.head;

    //Until I don't reach the end of my queue, I compare each element of the two queues
    while(unsigned long i=0; i<Size(); i++){
        if(elements[i] != elements[k])
            return false;
        //The modulo operator allows me to directly come back to index 0 when size i reached since n%n equals 0
        //that is the beggining of my array.
        //% is the rest of the division between A and B. If B>A (like here) it always returns A
        i = (i++) % size;
        k = (k++) % que.size;
    }

    return true;
}

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& que) const noexcept{
    return !(*this == que)
}

template <typename Data>
const Data& QueueVec<Data>::Head() const {
    if (!Empty())
        return Elements[head];
    
    throw std::length_error("Trying to access the head of an empty queue");
}

template <typename Data>
Data& QueueVec<Data>::Head(){
    if (!Empty())
        return Elements[head];
    
    throw std::length_error("Trying to access the head of an empty queue");
}

template <typename Data>
void QueueVec<Data>:Dequeue(){
    if (!Empty()){
        head = (++head) % size;
        if (Size() == size/4) 
            Reduce();
    } else 
        throw std::length_error("Trying to dequeue from an empty queue");
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue(){
    Data data = Head();
    Dequeue();
    return data;
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& data){
    if(Size() == size)
        Expand();
    tail = (++tail) % size;
    elements[tail] = data;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& data){
    if(Size() == size)
        Expand();
    tail = (++tail) % size;
    elements[tail] = std::move(data);
}

template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept{
    return (Size() == 0);
}

template <typename Data>
unsigned long QueueVec<Data>::Size() const noexcept{
    return ((tail-head+size+1)%size);
}

template<typename Data>
void QueueVec<Data>::Clear() noexcept{
    Vector<Data>::Clear();
    elements = new Data[2] {};
    size = 2;
    head = 0;
    tail = 0;
}

template<typename Data>
void Expand() noexcept{
    Data* tmp = new Data[size*2]{};
    unsigned long newSize = Size();

    for(unsigned long i = 0; i < newSize-1; i++){
        std::swap(elements[(head + i) % size], tmp[i]);
    }

    //In this way elements points to the tmp that I have just filled
    std::swap(elements, tmp);

    head = 0;
    tail = size - 1;
    size = size*2;
    
    delete[] tmp;
}

template<typename Data>
void Reduce() noexcept{
    Data* tmp = new Data[size/2]{};
    unsigned long newSize = Size();

    for(unsigned long i = 0; i < newSize-1; i++){
        std::swap(elements[(head + i) % size], tmp[i]);
    }

    //In this way elements points to the tmp that I have just filled
    std::swap(elements, tmp);

    head = 0;
    tail = size - 1;
    size = size/2;
    
    delete[] tmp;
}  
/* ************************************************************************** */

}
