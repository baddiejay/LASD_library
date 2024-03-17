
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

//Versione non mutable
template <typename Data>
inline const Data& LinearContainer<Data>::Front() const{
   if(size != 0)
   	return operator[](0);
   else
   	throw std::length_error("Trying to access to an empty container");
}

//Versione mutable
template <typename Data>
inline Data& LinearContainer<Data>::Front(){
   if(size != 0)
   	return operator[](0);
   else
   	throw std::length_error("Trying to access to an empty container");
}

//Versione non mutable
template <typename Data>
inline const Data& LinearContainer<Data>::Back() const{
   if(size != 0)
   	return operator[](size - 1);
   else
   	throw std::length_error("Trying to access to an empty container");
}

//Versione mutable
template <typename Data>
inline Data& LinearContainer<Data>::Back(){
   if(size != 0)
   	return operator[](size - 1);
   else
   	throw std::length_error("Trying to access to an empty container");
}

template <typename Data>
inline void LinearContainer<Data>::Fold(FoldFunctor fun, void* acc) const{
  PreOrderFold(fun, acc);
}

template <typename Data>
inline void LinearContainer<Data>::PreOrderFold(FoldFunctor fun, void* acc) const{
  for(unsigned long i = 0; i < size; i++){
    fun(operator[](i), acc);
  }
}

template <typename Data>
inline void LinearContainer<Data>::PostOrderFold(FoldFunctor fun, void* acc) const{
  unsigned long i = size;

  while(i > 0)
    fun(operator[](--i), acc);
  //L'indice è da 0 a n-1 dunque decremento prima
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
  //L'indice è da 0 a n-1 dunque decremento prima
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
  //L'indice è da 0 a n-1 dunque decremento prima
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

