
#include <stdexcept>

/* ************************************************************************** */

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

//Since I know how to do the Fold in one order, I can also do the generic Fold calling the one that I know how to do
template <typename Data>
inline void LinearContainer<Data>::Fold(FoldFunctor fun, void* acc) const{
  PreOrderFold(fun, acc);
}

template <typename Data>
inline void LinearContainer<Data>::PreOrderFold(FoldFunctor fun, void* acc) const{
  //On each element of my LinearContainer, I call the function with the function pointer FoldFunctor fun which takes a 
  //Data parameter (the i-th element access with operator[]) and stores the result in the acc pointer
  for(unsigned long i = 0; i < size; i++){
    fun(operator[](i), acc);
  }
}

template <typename Data>
inline void LinearContainer<Data>::PostOrderFold(FoldFunctor fun, void* acc) const{
  unsigned long i = size;

  while(i > 0)
    fun(operator[](--i), acc);
  //The index is from 0 to n-1 so decrease first
}

template <typename Data>
inline void LinearContainer<Data>::Map(MapFunctor fun) const{
  PreOrderMap(fun);
}

template <typename Data>
inline void LinearContainer<Data>::PreOrderMap(MapFunctor fun) const{
  for(unsigned long i = 0; i < size; i++){
    fun(operator[](i));
  }
}

template <typename Data>
inline void LinearContainer<Data>::PostOrderMap(MapFunctor fun) const{
  unsigned long i = size;

  while(i > 0)
    fun(operator[](--i));
  //The index is from 0 to n-1 so decrease first
}

template <typename Data>
inline void LinearContainer<Data>::Map(MutableMapFunctor fun){
  PreOrderMap(fun);
}

template <typename Data>
inline void LinearContainer<Data>::PreOrderMap(MutableMapFunctor fun){
  for(unsigned long i = 0; i < size; i++){
    fun(operator[](i));
  }
}

template <typename Data>
inline void LinearContainer<Data>::PostOrderMap(MutableMapFunctor fun){
  unsigned long i = size;

  while(i > 0)
    fun(operator[](--i));
  //The index is from 0 to n-1 so decrease first
}

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
/* ************************************************************************** */

}

