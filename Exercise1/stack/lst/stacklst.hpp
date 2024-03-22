
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual protected List<Data>,
                 virtual public Stack<Data> {
                  // Must extend Stack<Data>,
                  //             List<Data>

private:

  // ...

protected:

  using List<Data>::size;

  // ...

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  //Calling directly the constructor of the class List
  StackLst(const MappableContainer<Data>& mc) : List<Data>(mc) {}; // A stack obtained from a MappableContainer
  StackLst(MutableMappableContainer<Data>&& mmc) noexcept : List<Data>(mmc) {}; // A stack obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const Stack<Data>& cpy) : List<Data>(cpy) {};

  // Move constructor
  StackLst(Stack<Data>&& mve) noexcept : List<Data>(std::move(mve)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst<Data>& operator=(const StackLst<Data>&);

  // Move assignment
  StackLst<Data>& operator=(StackLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const StackLst<Data>&) const noexcept;
  inline bool operator!=(const StackLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
