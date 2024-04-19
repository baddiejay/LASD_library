
#ifndef MYTEST_HPP
#define MYTEST_HPP


#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../container/container.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

namespace lasd
{
  void Menu();

  //*******************VECTOR
  template<typename Data>
  void riempi(Vector<Data>& v);
  void riempi(Vector<std::string>& v);

  template<typename Data>
  Data& getIndexOf(Vector<Data>& v, int index);

  //*******************LIST
  template<typename Data>
  void riempi(List<Data>& list, unsigned int dim);
  void riempi(List<std::string>& list, unsigned int dim);
  
  //*******************QUEUE E STACK
  template <typename Data>
  void riempi(lasd::StackVec<Data>& v, unsigned int n);
  template <typename Data>
  void riempi(lasd::StackLst<Data>& v, unsigned int n);
  void MenuUtente();
  void MenuQueue(int tipo, int sceltaVettList, int n);
  void MenuStack(int tipo, int sceltaVettList, int n);
  
  
  void MenuUtente();
  void MenuQueue(int tipo, int sceltaVettList, int n);
  void MenuStack(int tipo, int sceltaVettList, int n);
  
  //*******************COMMON
  template <typename Data, typename Value>
  void FoldPreOrder(const lasd::PreOrderTraversableContainer<Data> & con, typename lasd::TraversableContainer<Data>::FoldFun<Value> fun, const Value & inival);
  
  template <typename Data>
  Data FoldAdd(const Data & dat, const Data & acc);
  
  template <typename Data>
  Data FoldMultiply(const Data & dat, const Data & acc);
  
  std::string FoldStringConcatenate(const std::string & dat, const std::string & acc);
}


#endif
