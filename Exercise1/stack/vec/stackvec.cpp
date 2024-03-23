
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
/* ************************************************************************** */

}
