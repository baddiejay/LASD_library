
namespace lasd {

/* ************************************************************************** */
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& st) noexcept : Vector<Data>(std::move(st)){
    std::swap(index, st.index);
}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& st){
    Vector<Data>::operator=(st);
    index = st.index
    return *this;
}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& st) noexcept{
    Vector<Data>::operator=(std::move(st));
    std::swap(index, st.index);
    return *this;
}

template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& st) const noexcept{
    if(index != st.index)
        return false;
    for(unsigned long i = 0; i < index; i++){
        if(elements[i] != st.elements[i])
            retunr false;
    }
    
    return true;
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& sr) const noexcept{
    return !(*this == st)
}

template <typename Data>
const Data& StackVec<Data>::Top() const{
    if(index != 0)
        return elements[index - 1];
    
    throw std::length_error("Trying to access the top on an empty stack");
}
template <typename Data>
Data& StackVec<Data>::Top(){
    if(index != 0)
        return elements[index - 1];
    
    throw std::length_error("Trying to access the top on an empty stack");
}

template <typename Data>
void StackVec<Data>::Pop(){
    //I don't need to delete the value, it will be overwritten with the next push on the same index
    if(index != 0){
        index--;
        //If I'm using only a small fraction of my space then I have to shrink my vector.
        //I do it if the space occupied is less than one quarter of the available space
        if(index < size/4)
            Reduce();
    } else
        throw std::length_error("Trying to access the top on an empty stack");
}

template <typename Data>
Data StackVec<Data>::TopNPop(){
    if(index != 0){
        Data value = Top();
        Pop();
        return value;
    } else
        throw std::length_error("Trying to access the top on an empty stack");
}

template <typename Data>
void StackVec<Data>::Push(const Data& d){
    //Index points to the first available cell
    if(--index == size){
        Expand();
    }

    elements[index++] = d;
}

template <typename Data>
void StackVec<Data>::Push(Data&& d){
    if(--index == size){
        Expand();
    }

    elements[index++] = d;
}

template <typename Data>
inline bool StackVec<Data>::Empty() const noexcept{
    //The meaning is that no data is in the stack, not that the array has dimension 0
    return (index == 0)
}


template <typename Data>
inline unsigned long StackVec<Data>::Size() const noexcept{
    //Size doesn't correspond to the allocated memory cells but to how many elements are in the stack
    return index;
}

template <typename Data>
void StackVec<Data>::Clear(){
    for(ulong i=stackSize; i>0; i--){
        Pop();
    }
}

template <typename Data>
void StackVec<Data>::Expand() noexcept{
    Vector<Data>::Resize(size * 2);
}

template <typename Data>
void StackVec<Data>::Reduce() noexcept{
    //I'm going to reduce if one quarter only is occupied so..
    Vector<Data>::Resize((size*3) / 4);
}
/* ************************************************************************** */

}
