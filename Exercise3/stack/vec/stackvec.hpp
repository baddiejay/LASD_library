
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

  //Points to the first available cell
  unsigned long index = 0;

  using Vector<Data>::size;
  using Vector<Data>::elements;

public:

  // Default constructor
  //The stack is empty but the array has already two cells allocated in order to avoid to do an expansion on the first push
  StackVec() : Vector<Data>(2) {}

  /* ************************************************************************ */

  // Specific constructor

  StackVec(const TraversableContainer<Data>& mc) : Vector<Data>(mc), index(size) {}; // A stack obtained from a MappableContainer
  StackVec(const MappableContainer<Data>&& mmc) noexcept : Vector<Data>(std::move(mmc)), index(size) {}; // A stack obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data>& st) : Vector<Data>(st), index(st.index) {};

  // Move constructor
  StackVec(StackVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

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
  //Accessing the cell with index-1 from the the pointer to the available cell
  const Data& Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  //Insert in the place con the index and then incrementing the index 
  //If the available space is not enough we have to extend the vector before inserting
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) noexcept override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override; // Override Container member

  //Size doesn't correspond to the allocated memory cells but to how many elements are in the stack

  inline unsigned long Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  //In this case I don't want to empty all the array making it of dimension 0, INSTEAD
  //I want to leave some space in order to be ablre to do some pushes without resizing the vector
  void Clear() noexcept override; // Override ClearableContainer member

protected:

  // Auxiliary member functions

  void Expand() noexcept;
  void Reduce() noexcept;

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
