
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline bool FoldableContainer<Data>::Exists(const Data& d) const noexcept{
  bool exists = false;
  //Attenzione qua a |= e non =
  //La fold prende un puntatore void e restituisce un void quindi &exists è automaticamente convertito a void
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
