
namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data>& mc) : Vector<Data>(mc){
    head = 0;
    tail = size;
    Vector<Data>::Resize(size*2);
}

template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data>&& mmc) noexcept : Vector<Data>(std::move(mmc)){
    head = 0;
    tail = size;
    Vector<Data>::Resize(size*2);
}

template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& cpy) : Vector<Data>(cpy){
    head = cpy.head;
    tail = cpy.tail;
}

template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& mov) noexcept : Vector<Data>(std::move(mov)){
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
    if(Size() != que.Size()){
        return false;
    }

    unsigned long j = head;
    unsigned long k = que.head;

    //Until I don't reach the end of my queue, I compare each element of the two queues
    for(unsigned long i=0; i<Size(); i++){
        if(elements[j] != que.elements[k]){
            return false;
        }
        //The modulo operator allows me to directly come back to index 0 when size i reached since n%n equals 0
        //that is the beggining of my array.
        //% is the rest of the division between A and B. If B>A (like here) it always returns A
        j = (j+1) % size;
        k = (k+1) % que.size;
    }

    return true;
}

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& que) const noexcept{
    return !(*this == que);
}

template <typename Data>
const Data& QueueVec<Data>::Head() const {
    if (!Empty()){
        return elements[head];
    } else {
        throw std::length_error("Trying to access the head of an empty queue");
    }
}

template <typename Data>
Data& QueueVec<Data>::Head(){
    if (!Empty()){
        return elements[head];
    } else {
        throw std::length_error("Trying to access the head of an empty queue");
    }
}

template <typename Data>
void QueueVec<Data>::Dequeue(){
    if (!Empty()){
    	++head %= size;
        Reduce();   
    } else {
        throw std::length_error("Trying to dequeue from an empty queue");
    }
}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue(){
    if (!Empty()){
        Reduce();
        Data dat(std::move(elements[head]));
        ++head %= size;  
        return dat; 
    } else {
        throw std::length_error("Trying to dequeue from an empty queue");
    }
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& data){
    Expand();
    // I write and move tail forward
    elements[tail++] = data;
    tail %= size;
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& data){
    Expand();
    elements[tail++] = std::move(data);
    tail %= size;
}

template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept{
    return ((head == tail));
}

template <typename Data>
unsigned long QueueVec<Data>::Size() const noexcept{
    return (((tail + size) - head) % size);
}

template<typename Data>
void QueueVec<Data>::Clear() noexcept{
    head = tail = 0;
    Vector<Data>::Resize(4);
}

template<typename Data>
void QueueVec<Data>::ResizeQueue(unsigned long newSize, unsigned long num){
    Data* tmp = new Data[newSize];
    unsigned long max = (num <= newSize) ? num : newSize;
    for(unsigned long idx1 = head, idx2 = 0; idx2 < max; ++idx1 %= size, ++idx2){
        std::swap(elements[idx1], tmp[idx2]);
    }
    //In this way elements points to the tmp that I have just filled
    std::swap(elements, tmp);
    delete[] tmp;
    head = 0;
    tail = num;
    size = newSize;
}


template<typename Data>
void QueueVec<Data>::Reduce() noexcept{
    unsigned long num = Size();
    // Size() gives me the number of elements actually contained in the queue. 
    //When this is 1/4 of the allocated space (size) then I have to reduce the vector
    if(num + 1 == size / 4){
        ResizeQueue(size / 2, num);
    }
}  

template<typename Data>
void QueueVec<Data>::Expand() noexcept{
    unsigned long num = Size();
    if(num + 1 == size){
        ResizeQueue(size * 2, num);
    }
}  
/* ************************************************************************** */

}
