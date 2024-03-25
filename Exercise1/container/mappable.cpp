
#include <stdexcept>
#include <iostream>
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline void MappableContainer<Data>::Fold(FoldFunctor fun, void* acc) const {
  //The map receives as input the lambda function that invokes fun on the d element
  Map([fun, acc](const Data& d) {fun(d,acc);});
};

//PREORDER-------------------------------------------------
template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFunctor fun) const {
  PreOrderMap(fun);
};

/*template <typename Data>
inline void PreOrderMappableContainer<Data>::Fold(MapFunctor fun, void* acc) const {
  PreOrderFold(fun, acc);
};*/

template <typename Data>
inline void PreOrderMappableContainer<Data>::PreOrderFold(FoldFunctor fun, void* acc) const {
  PreOrderMap([fun, acc](const Data& d) {fun(d,acc);});
}

//POSTORDER-------------------------------------------------
template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFunctor fun) const {
  PostOrderMap(fun);
};

/*template <typename Data>
inline void PostOrderMappableContainer<Data>::Fold(MapFunctor fun, void* acc) const {
  PostOrderFold(fun, acc);
};*/

template <typename Data>
inline void PostOrderMappableContainer<Data>::PostOrderFold(FoldFunctor fun, void* acc) const {
  PostOrderMap([fun, acc](const Data& d) {fun(d,acc);});
}

//INORDER-------------------------------------------------
template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFunctor fun) const {
  InOrderMap(fun);
};

/*template <typename Data>
inline void InOrderMappableContainer<Data>::Fold(MapFunctor fun, void* acc) const {
  InOrderFold(fun, acc);
};*/

template <typename Data>
inline void InOrderMappableContainer<Data>::InOrderFold(FoldFunctor fun, void* acc) const {
  InOrderMap([fun, acc](const Data& d) {fun(d,acc);});
}

//BREADTHORDER-------------------------------------------------
template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFunctor fun) const {
  BreadthMap(fun);
};

/*
template <typename Data>
inline void BreadthMappableContainer<Data>::Fold(MapFunctor fun, void* acc) const {
  BreadthFold(fun, acc);
};*/

template <typename Data>
inline void BreadthFoldableContainer<Data>::BreadthFold(FoldFunctor fun, void* acc) const {
  BreadthMap([fun, acc](const Data& d) {fun(d,acc);});
}

//-------------------------- MUTABLE
template <typename Data>
inline void MutablePreOrderMappableContainer<Data>::Map(MutableMapFunctor fun) {
  PreOrderMap(fun);
}

template <typename Data>
inline void MutablePostOrderMappableContainer<Data>::Map(MutableMapFunctor fun) {
  PostOrderMap(fun);
}

template <typename Data>
inline void MutableInOrderMappableContainer<Data>::Map(MutableMapFunctor fun) {
  InOrderMap(fun);
}

template <typename Data>
inline void MutableBreadthMappableContainer<Data>::Map(MutableMapFunctor fun) {
  BreadthMap(fun);
}
/* ************************************************************************** */

}
