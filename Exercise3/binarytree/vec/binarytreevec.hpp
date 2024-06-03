
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> {
                      // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  // ...
  using BinaryTree<Data>::size;

  struct NodeVec : virtual public MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

  private:

    // ...

  protected:

    // ...
    

  public:

    // ...

    Data data;
    Vector<NodeVec*> * tree = nullptr;
    unsigned long index = 0;

    NodeVec() = default;

    NodeVec(const Data&, ulong, Vector<NodeVec*> *);

    NodeVec(Data&&, ulong, Vector<NodeVec*> *);

    // Destructor
    virtual ~NodeVec() = default;

    // Specific member functions
    const Data& Element() const noexcept override;
    Data& Element() noexcept override;
    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;
    const NodeVec& LeftChild() const override;
    const NodeVec& RightChild() const override;
    NodeVec& LeftChild() override;
    NodeVec& RightChild() override;

  };

  Vector<NodeVec*> * vectorTree = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data> & container); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data> && container) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec<Data>& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec<Data>& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // type Root() specifiers; 
  const NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;

  void BreadthTraverse(TraverseFun fun) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  using typename MappableContainer<Data>::MapFun;

  void BreadthMap(MapFun fun) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */


};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
