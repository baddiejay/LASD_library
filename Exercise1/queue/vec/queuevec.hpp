
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>

class QueueVec : virtual public Queue<Data>,
                 virtual protected Vector<Data>{
                  // Must extend Queue<Data>,
                  //             Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::elements;

  unsigned long head = 0;
  unsigned long tail = 0;

public:

  // Default constructor
  QueueVec() : Vector<Data>(4) {};

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data>&); // A queue obtained from a MappableContainer
  QueueVec(MappableContainer<Data>&&) noexcept; // A queue obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data>&);

  // Move constructor
  QueueVec(QueueVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec<Data>& operator=(const QueueVec<Data>&);

  // Move assignment
  QueueVec<Data>& operator=(QueueVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec<Data>&) const noexcept;
  inline bool operator!=(const QueueVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  inline bool Empty() const noexcept override; // Override Container member
  unsigned long Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() noexcept override; // Override ClearableContainer member

protected:

  // Auxiliary member functions
  void Expand() noexcept;
  void Reduce() noexcept;
  void Resize(unsigned long newSize, unsigned long num);

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
