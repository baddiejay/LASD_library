
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {
                      // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeLnk : virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

    private:
  
      // ...
  
    protected:
  
      // ...
  
    public:
  
      // ...
      Data data {};
      
      NodeLnk * leftChild = nullptr;
      NodeLnk * rightChild = nullptr;

      //Default constructor
      NodeLnk() = default;
    
      //Specific constructor
      NodeLnk(const Data&);

      //Specific move constructor
      NodeLnk(Data&&) noexcept;

      //Destructor
      virtual ~NodeLnk();

      //Specific member functions 
      inline const Data& Element() const noexcept override;
      inline Data& Element() noexcept override;
      inline bool HasLeftChild() const noexcept override;
      inline bool HasRightChild() const noexcept override;
      const NodeLnk& LeftChild() const override;
      const NodeLnk& RightChild() const override;
      NodeLnk& LeftChild() override;
      NodeLnk& RightChild() override;

      //Any other method that is not overridden is automatically taken from the base class
  };

  NodeLnk * root = nullptr;

  NodeLnk* recursiveCopyTree(NodeLnk*);

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> & container); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data> && container) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  const NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  NodeLnk& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() noexcept override;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
