
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
      Data data;
      
      NodeLnk * leftChild = nullptr;
      NodeLnk * rightChild = nullptr;
  
      NodeLnk(const Data&);
  
      NodeLnk(Data&&) noexcept;
  
      virtual ~NodeLnk();
  
      const Data& Element() const noexcept override;
      Data& Element() noexcept override;
      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;
      NodeLnk& LeftChild() const override;
      NodeLnk& RightChild() const override;
      NodeLnk& LeftChild() override;
      NodeLnk& RightChild() override;
  
  };

  NodeLnk * root = nullptr;

  NodeLnk* recursiveCopyTree(NodeLnk*);

public:

  // Default constructor
  // BinaryTreeLnk() specifiers;
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a MappableContainer
  BinaryTreeLnk(const TraversableContainer<Data> & container);
  // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a MutableMappableContainer
  BinaryTreeLnk(MappableContainer<Data> && container) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // BinaryTreeLnk(argument) specifiers;
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  // BinaryTreeLnk(argument) specifiers;
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BinaryTreeLnk() specifiers;
  virtual ~BinaryTreeLnk();


  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  // type operator=(argument) specifiers;
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BinaryTreeLnk&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)
  NodeLnk& Root() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  // type Root() specifiers; // Override MutableBinaryTree member (throw std::length_error when empty)
  NodeLnk& Root() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  void Clear() noexcept override;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
