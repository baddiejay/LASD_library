
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */
//Users can see and use the methods of the Queue interface (public inheritance) which are implemented using 
//the methods of List that are not visible and usable from the user but only inside this class (protected inheritance)
template <typename Data>
class QueueLst : virtual protected List<Data>
                 virtual public Queue<Data>{
                  // Must extend Queue<Data>,
                  //             List<Data>

private:

  // ...

protected:

  using List<Data>::size;

  // ...

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const MappableContainer<Data>& mc) : List<Data>(mc) {}; // A queue obtained from a MappableContainer
  QueueLst(MappableContainer<Data>&& mmc) noexcept : List<Data>(std::move(mmc)) {}; // A queue obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst<Data>& cpy) : List<Data>(cpy) {};

  // Move constructor
  QueueLst(QueueLst<Data>&& cpy) noexcept : List<Data>(std::move(mve)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueLst<Data>& operator=(const QueueLst<Data>&);

  // Move assignment
  QueueLst<Data>& operator=(const QueueLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const QueueLst<Data>&) const noexcept;
  inline bool operator!=(const QueueLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
