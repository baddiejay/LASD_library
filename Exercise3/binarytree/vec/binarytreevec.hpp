
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

    Data data {};
    Vector<NodeVec*> * tree = nullptr;
    unsigned long index = 0;

    //Default constructor
    NodeVec() = default;
    
    //Specific constructor
    NodeVec(const Data&, unsigned long, Vector<NodeVec*> *);
    
    //Specific move constructor
    NodeVec(Data&&, unsigned long, Vector<NodeVec*> *);

    //Destructor
    virtual ~NodeVec() = default;

    //Specific member functions 
    inline const Data& Element() const noexcept override;
    inline Data& Element() noexcept override;
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;
    const NodeVec& LeftChild() const override;
    const NodeVec& RightChild() const override;
    NodeVec& LeftChild() override;
    NodeVec& RightChild() override;
    
    //Any other method that is not overridden is automatically taken from the base class

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

  const NodeVec& Root() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  NodeVec& Root() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer))
  using typename TraversableContainer<Data>::TraverseFun;

  void BreadthTraverse(TraverseFun fun) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)
  using typename MappableContainer<Data>::MapFun;

  void BreadthMap(MapFun fun) override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */


};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
