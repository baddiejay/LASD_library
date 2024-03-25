
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

//Even if the fold is not implemented, the existis works based on the fold that someone else will implement for me
template <typename Data>
inline bool FoldableContainer<Data>::Exists(const Data& d) const noexcept{
  bool exists = false;
  //FOLD takes as a parameter a function of tipe FoldFunctor and a void* accumulator (&exists).
  //The FoldFunctor function returns void and has 2 parameters:
  // 1) of type Data&, 2) a pointer of type void*
  //I'm using the OR assignment to check for each element d if it is equal to a value val I already have in my structure
  Fold([d](const Data& val, void* acc) {*((bool*)acc) |= (d == val);}, &exists);
  return exists;
}

template <typename Data>
inline void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, void* acc) const {
  PreOrderFold(fun, acc);
}

template <typename Data>
inline void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun, void* acc) const {
  PostOrderFold(fun, acc);
}

template <typename Data>
inline void InOrderFoldableContainer<Data>::Fold(FoldFunctor fun, void* acc) const {
  InOrderFold(fun, acc);
}

template <typename Data>
inline void BreadthFoldableContainer<Data>::Fold(FoldFunctor fun, void* acc) const {
  BreadthFold(fun, acc);
}
/* ************************************************************************** */

}
