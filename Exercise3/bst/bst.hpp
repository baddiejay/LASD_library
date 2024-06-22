
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer, 
            virtual public DictionaryContainer<Data>,
            virtual public BinaryTree<Data>,
            virtual protected BinaryTreeLnk<Data> {
            // Must extend ClearableContainer,
            //             DictionaryContainer<Data>,
            //             BinaryTree<Data>,
            //             BinaryTreeLnk<Data>

private:

  // ...

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;
  // It's used in template contexts when dealing with template-dependent types. 
  //It serves to indicate that a specified name is a type and not a static member or function.
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data> & container); // A bst obtained from a TraversableContainer
  BST(MappableContainer<Data> && container) noexcept; // A bst obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST&) const noexcept;
  inline bool operator!=(const BST&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions 
  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when empty)ù
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)ù
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when empty)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when empty)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when empty)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */
  
  // Specific member functions (inherited from BinaryTree)
  using BinaryTreeLnk<Data>::Root;
  
  /* ************************************************************************ */
   
  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) noexcept override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  using BinaryTreeLnk<Data>::Clear; // Override ClearableContainer member

protected:

  // Auxiliary member functions
  Data DataNDelete(NodeLnk*);
  
  NodeLnk* Detach(NodeLnk * &) noexcept;
  NodeLnk* DetachMin(NodeLnk*&) noexcept;
  NodeLnk* DetachMax(NodeLnk*&) noexcept;

  NodeLnk* Skip2Left(NodeLnk*&) noexcept;
  NodeLnk* Skip2Right(NodeLnk*&) noexcept;

  const NodeLnk* const& FindPointerToMin(const NodeLnk* const&) const noexcept; // Both mutable & unmutable versions
  NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept;

  const NodeLnk* const& FindPointerToMax(const NodeLnk* const&) const noexcept; // Both mutable & unmutable versions
  NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept;

  const NodeLnk* const& FindPointerTo(const NodeLnk* const&, const Data&) const noexcept; // Both mutable & unmutable versions
  NodeLnk*& FindPointerTo(NodeLnk*&, const Data&) noexcept;

  const NodeLnk* const* FindPointerToPredecessor(const NodeLnk* const&, const Data&) const noexcept; // Both mutable & unmutable versions
  NodeLnk** FindPointerToPredecessor(NodeLnk*&, const Data&) noexcept;

  const NodeLnk* const* FindPointerToSuccessor(const NodeLnk* const&, const Data&) const noexcept; // Both mutable & unmutable versions
  NodeLnk** FindPointerToSuccessor(NodeLnk*&, const Data&) noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
