
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {
                        // Must extend HashTable<Data>

private:

  // ...
  
protected:

  using DictionaryContainer<Data>::size;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::tableSize;

  Vector<Data> table;
  Vector<char> flags;

public:

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const unsigned long size); 
  HashTableOpnAdr(const TraversableContainer<Data> & container); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(const unsigned long size, const TraversableContainer<Data> & container); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data> && container) noexcept; // A hash table obtained from a MappableContainer
  HashTableOpnAdr(unsigned long size, MappableContainer<Data> && container) noexcept; // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  ~HashTableOpnAdr() = default;
  
  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(const unsigned long) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  unsigned long HashKey(const Data& data, unsigned long i) const noexcept;
  unsigned long Find(const Data& data) const noexcept;
  unsigned long FindEmpty(const Data& data) const noexcept;
  
  void initEmptyFlags() noexcept {
    for(unsigned long i = 0; i < tableSize; i++){
      flags[i] = 'E';
    }
  }

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
