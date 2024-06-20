
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  virtual unsigned long operator()(const Data&) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer, virtual public DictionaryContainer<Data>{
                  // Must extend ResizableContainer,
                  //             DictionaryContainer<Data>

private:

protected:

  //Takes into account the number of elements present, different from the size of the table
  using DictionaryContainer<Data>::size;

  unsigned long a = 3;
  unsigned long b = 7;
  
  static const unsigned long prime = 1000000033;
  unsigned long tableSize = 128;
  
  static const Hashable<Data> enhash;

  std::default_random_engine gen = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<unsigned long> genA = std::uniform_int_distribution<unsigned long>(1, prime);
  std::uniform_int_distribution<unsigned long> genB = std::uniform_int_distribution<unsigned long>(0, prime);

  //Default constructor
  HashTable() {
    a = (genA(gen) * 2) + 1;
    b = genB(gen);
  }

  //Copy constructor
  HashTable(const HashTable&);

  //Move constructor
  HashTable(HashTable&&) noexcept;
  
  // Copy assignment
  HashTable& operator=(const HashTable&) ; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept; // Move assignment of abstract types should not be possible.

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable&) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  virtual unsigned long HashKey(unsigned long key) const noexcept {
     return ((a * key + b) % prime) % tableSize;
  }
  
  virtual unsigned long HashKey(const Data& dat) const noexcept {
     return HashKey(enhash.operator()(dat));
  }
  
};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
