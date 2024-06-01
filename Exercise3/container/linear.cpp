
namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool inline LinearContainer<Data>::operator==(const LinearContainer<Data> & lc) const noexcept{
   if(size != lc.size)
   	return false;
   for(unsigned long i = 0; i < size; i++){
   	if(operator[](i) != lc[i])
   	   return false;
   }
   return true;

}

template <typename Data>
bool inline LinearContainer<Data>::operator!=(const LinearContainer<Data>& lc) const noexcept{
   return !(*this == lc);
}

template <typename Data>
inline const Data& LinearContainer<Data>::Front() const{
   if(size != 0)
   	return operator[](0);
   else
   	throw std::length_error("Trying to access to an empty container");
}

template <typename Data>
inline Data& LinearContainer<Data>::Front(){
   if(size != 0)
   	return operator[](0);
   else
   	throw std::length_error("Trying to access to an empty container");

}

//Non mutable version which is const and returns a const reference so nothing can be modified
template <typename Data>
inline const Data& LinearContainer<Data>::Back() const{
   if(size != 0)
   	return operator[](size - 1);
   else
   	throw std::length_error("Trying to access to an empty container");
}

//Mutable version
template <typename Data>
inline Data& LinearContainer<Data>::Back(){
   if(size != 0)
   	return operator[](size - 1);
   else
   	throw std::length_error("Trying to access to an empty container");
}

template<typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

template<typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
    for(unsigned long i = 0; i < size; i++){
        fun(operator[](i));
    }
}

template<typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const{
    unsigned long i = size;

    while(i > 0)
        fun(operator[](--i));
     //The index is from 0 to n-1 so decrease first
}

template<typename Data>
inline void LinearContainer<Data>::Map(MapFun fun){
    PreOrderMap(fun);
}

template<typename Data>
inline void LinearContainer<Data>::PreOrderMap(MapFun fun){
    for(unsigned long i = 0; i < size; i++){
        fun(operator[](i));
    }
}

template<typename Data>
inline void LinearContainer<Data>::PostOrderMap(MapFun fun){
    unsigned long i = size;

    while(i > 0)
        fun(operator[](--i));
     //The index is from 0 to n-1 so decrease first
}

//************************* SORTABLE *********************
template <typename Data>
bool inline SortableLinearContainer<Data>::operator==(const SortableLinearContainer<Data> & lc) const noexcept{
   if(size != lc.size)
   	return false;

   for(unsigned long i = 0; i < size; i++){
   	if(operator[](i) != lc[i])
   	   return false;
   }

   return true;
}

template <typename Data>
bool SortableLinearContainer<Data>::operator!=(const SortableLinearContainer<Data>& slc) const noexcept{
  return !(*this == slc);
}

template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept{
    QuickSort(0, size - 1);
}

template<typename Data>
void SortableLinearContainer<Data>::QuickSort(unsigned long p, unsigned long r) noexcept{
    if(p < r){
        unsigned long q = Partition(p, r);
        QuickSort(p, q);
        QuickSort(q + 1, r);
    }
}

template<typename Data>
unsigned long SortableLinearContainer<Data>::Partition(unsigned long p, unsigned long r) noexcept{
    Data x = operator[](p);
    unsigned long i = p - 1;
    unsigned long j = r + 1;
    do{
        do {j--;}
        while(x < operator[](j));
        do {i++;}
        while(x > operator[](i));
        if(i < j) { std::swap(operator[](i), operator[](j));}
    } while (i < j);

    return j;
}
/* ************************************************************************** */

}
