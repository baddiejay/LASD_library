
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
  // HashTableOpnAdr() specifiers;
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size
  HashTableOpnAdr(const unsigned long size); 
  // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const TraversableContainer<Data> & container);
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a MappableContainer
  HashTableOpnAdr(const unsigned long size, const TraversableContainer<Data> & container);
  // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a MutableMappableContainer
  HashTableOpnAdr(MappableContainer<Data> && container) noexcept;
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a MutableMappableContainer
  HashTableOpnAdr(unsigned long size, MappableContainer<Data> && container) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // HashTableOpnAdr(argument) specifiers;
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  // HashTableOpnAdr(argument) specifiers;
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  ~HashTableOpnAdr() = default;
  
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  // type operator=(argument) specifiers;
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const HashTableOpnAdr&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
  bool Insert(const Data&) override;
  // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  bool Insert(Data&&) override;
  // type Remove(argument) specifiers; // Override DictionaryContainer member
  bool Remove(const Data&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
  bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Resize the hashtable to a given size
  void Resize(const unsigned long) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  // type Clear() specifiers; // Override Container member
  void Clear() override;

protected:

  // Auxiliary member functions

  // type HashKey(argument) specifiers;
  unsigned long HashKey(const Data& data, unsigned long i) const noexcept;
  // type Find(argument) specifiers;
  unsigned long Find(const Data& data) const noexcept;
  // type FindEmpty(argument) specifiers;
  unsigned long FindEmpty(const Data& data) const noexcept;
  // type Remove(argument) specifiers;
  
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
