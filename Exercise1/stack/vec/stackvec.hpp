
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>,
                 virtual protected Vector<Data>{
                  // Must extend Stack<Data>,
                  //             Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;

  // ...

public:

  // Default constructor
  StackVec() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const MappableContainer<Data>&); // A stack obtained from a MappableContainer
  StackVec(const MutableMappableContainer<Data>&&) noexcept; // A stack obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data>&);

  // Move constructor
  StackVec(StackVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec<Data>& operator=(const StackVec<Data>&);

  // Move assignment
  StackVec<Data>& operator=(StackVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec<Data>&) const noexcept;
  inline bool operator!=(const StackVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  // type Top() specifiers; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  // type Top() specifiers; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  // type Pop() specifiers; // Override Stack member (must throw std::length_error when empty)
  // type TopNPop() specifiers; // Override Stack member (must throw std::length_error when empty)
  // type Push(argument) specifiers; // Override Stack member (copy of the value)
  // type Push(argument) specifiers; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Empty() specifiers; // Override Container member

  // type Size() specifiers; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member

protected:

  // Auxiliary member functions

  // type Expand() specifiers;
  // type Reduce() specifiers;

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
