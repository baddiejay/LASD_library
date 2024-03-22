
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public ResizableContainer, virtual public SortableLinearContainer<Data>{
                // Must extend ResizableContainer,
                //             SortableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size;
  
  Data* elements = nullptr;

public:

  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const unsigned long); // A vector with a given initial dimension
  //Scorro il container e popolo il mio array cella per cella
  Vector(const MappableContainer<Data>&); // A vector obtained from a MappableContainer
  //Siccome è mutable posso modificarlo allora meglio costruire per spostamento.
  Vector(MutableMappableContainer<Data>&&) noexcept; // A vector obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data>&);

  // Move constructor
  Vector(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector<Data>&);

  // Move assignment
  Vector& operator=(Vector<Data>&&) noexcept;

  /* ************************************************************************ */
  //Confronto prima la dimensione e poi scorro cella per cella
  // Comparison operators
  bool operator==(const Vector<Data>&) const noexcept;
  inline bool operator!=(const Vector<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  //Mette la size a 0 e delete del vettore
  void Clear() noexcept override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  //Alloco nuovo vettore, effettuo la copia e dealloco il vecchio o anche a decrescere data la nuova dimensione del vettore che voglio
  void Resize(const unsigned long) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const unsigned long) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data& operator[](const unsigned long) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  //Questo override non dovrebbe essere necessario
  const Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; // Override SortableLinearContainer member

protected:

  void quickSort(unsigned long, unsigned long) noexcept;
  unsigned long partition(unsigned long, unsigned long) noexcept;

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
