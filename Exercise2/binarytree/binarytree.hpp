
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../queue/vec/queuevec.hpp"

#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>,
                   virtual public PostOrderTraversableContainer<Data>, 
                   virtual public InOrderTraversableContainer<Data>, 
                   virtual public BreadthTraversableContainer<Data> {
                    // Must extend PreOrderTraversableContainer<Data>,
                    //             PostOrderTraversableContainer<Data>,
                    //             InOrderTraversableContainer<Data>,
                    //             BreadthTraversableContainer<Data>

private:

  // ...

protected:

  // ...

  using Container::size;

public:

  struct Node {

  protected:

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is possible, but should not be visible.
    bool operator==(const Node&) const noexcept;
    // type operator!=(argument) specifiers; // Comparison of abstract types is possible, but should not be visible.
    bool operator!=(const Node&) const noexcept;

  public:

    // friend class BinaryTree<Data>;
    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    // ~Node() specifiers
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.
    Node& operator=(const Node&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.
    Node& operator=(Node&&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions

    // type Element() specifiers; // Immutable access to the element (concrete function should not throw exceptions)
    // virtual const Data& Element() const noexcept = 0;
    virtual const Data& Element() const noexcept = 0;

    // type IsLeaf() specifiers; // (concrete function should not throw exceptions)
    virtual bool IsLeaf() const noexcept;
    // type HasLeftChild() specifiers; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; 
    // type HasRightChild() specifiers; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0;

    // type LeftChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    // virtual const Node& LeftChild() const = 0; 
    virtual Node& LeftChild() const = 0;
    // type RightChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    // virtual const Node& RightChild() const = 0;
    virtual Node& RightChild() const = 0;

  };

  /* ************************************************************************ */

  // Destructor
  // ~BinaryTree() specifiers
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  BinaryTree& operator=(const BinaryTree&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  BinaryTree& operator=(BinaryTree&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract binary tree is possible.
  bool operator==(const BinaryTree&) const noexcept;
  // type operator!=(argument) specifiers; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type Root() specifiers; // (concrete function must throw std::length_error when empty)
  virtual Node& Root() const = 0;

 
  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  void InOrderTraverse(TraverseFun) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

protected:

  void PreOrderTraverse(TraverseFun fun, const Node * cur) const;

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)

  // type PostOrderMap(arguments) specifiers; // Accessory function executing from one node of the tree
  void PostOrderTraverse(TraverseFun fun, const Node * cur) const;

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)

  // type InOrderMap(arguments) specifiers; // Accessory function executing from one node of the tree
  void InOrderTraverse(TraverseFun fun, const Node * cur) const;

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)

  // type BreadthMap(arguments) specifiers; // Accessory function executing from one node of the tree
  void BreadthTraverse(TraverseFun fun, const Node * cur) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,
                          virtual public BinaryTree<Data>,
                          virtual public PreOrderMappableContainer<Data>,
                          virtual public PostOrderMappableContainer<Data>, 
                          virtual public InOrderMappableContainer<Data>, 
                          virtual public BreadthMappableContainer<Data>{
                          // Must extend ClearableContainer,
                          //             BinaryTree<Data>,
                          //             MutablePreOrderMappableContainer<Data>,
                          //             MutablePostOrderMappableContainer<Data>,
                          //             MutableInOrderMappableContainer<Data>,
                          //             MutableBreadthMappableContainer<Data>

private:

  // ...

protected:

  // ...
  using Container::size;

public:

  struct MutableNode : virtual public BinaryTree<Data>::Node {
                        // Must extend Node

    // friend class MutableBinaryTree<Data>;
    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    // ~MutableNode() specifiers
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.
    MutableNode& operator=(const MutableNode&) = delete;

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.
    MutableNode& operator=(MutableNode&&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions

    // type Element() specifiers; // Mutable access to the element (concrete function should not throw exceptions)
    virtual Data& Element() noexcept = 0;

    // type LeftChild() specifiers; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode& LeftChild() = 0;

    // type RightChild() specifiers; // (concrete function must throw std::out_of_range when not existent)    
    virtual MutableNode& RightChild() = 0;
  };

  /* ************************************************************************ */

  // Destructor
  // ~MutableBinaryTree() specifiers
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  MutableBinaryTree& operator=(const MutableBinaryTree&) = delete;
  

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  MutableBinaryTree& operator=(MutableBinaryTree&&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Root() specifiers; // (concrete function must throw std::length_error when empty)  
  virtual MutableNode& Root() = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  // using typename MutableMappableContainer<Data>::MutableMapFunctor;
  using typename MappableContainer<Data>::MapFun;

  // type Map(arguments) specifiers; // Override MutableMappableContainer member
  void Map(MapFun fun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  // type PreOrderMap(arguments) specifiers; // Override MutablePreOrderMappableContainer member
  void PreOrderMap(MapFun fun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  // type PostOrderMap(arguments) specifiers; // Override MutablePostOrderMappableContainer member
  void PostOrderMap(MapFun fun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableInOrderMappableContainer)

  // type InOrderMap(arguments) specifiers; // Override MutableInOrderMappableContainer member
  void InOrderMap(MapFun fun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBreadthMappableContainer)

  // type BreadthMap(arguments) specifiers; // Override MutableBreadthMappableContainer member
  void BreadthMap(MapFun fun) override;

protected:

  // Auxiliary member function (for MutablePreOrderMappableContainer)

  // type PreOrderMap(arguments) specifiers; // Accessory function executing from one node of the tree
  void PreOrderMap(MapFun fun, MutableNode * cur);

  /* ************************************************************************ */

  // Auxiliary member function (for MutablePostOrderMappableContainer)

  // type PostOrderMap(arguments) specifiers; // Accessory function executing from one node of the tree
  void PostOrderMap(MapFun fun, MutableNode * cur);

  /* ************************************************************************ */

  // Auxiliary member function (for MutableInOrderMappableContainer)

  // type InOrderMap(arguments) specifiers; // Accessory function executing from one node of the tree
  void InOrderMap(MapFun fun, MutableNode * cur);

  /* ************************************************************************ */

  // Auxiliary member function (for MutableBreadthMappableContainer)

  // type BreadthMap(arguments) specifiers; // Accessory function executing from one node of the tree
  void BreadthMap(MapFun fun, MutableNode * cur);

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>, 
                           virtual public ResettableIterator<Data> {
                           // Must extend ForwardIterator<Data>,
                           //             ResettableIterator<Data>

private:

  // ...

protected:

  // ...

 // using typename BinaryTree<Data>::Node;
  
  typename BinaryTree<Data>::Node * current = nullptr;

  typename BinaryTree<Data>::Node * root = nullptr;
  
  StackLst<typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  // BTPreOrderIterator(argument) specifiers; // An iterator over a given binary tree
  BTPreOrderIterator(const BinaryTree<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // BTPreOrderIterator(argument) specifiers;
  BTPreOrderIterator(const BTPreOrderIterator&);

  // Move constructor
  // BTPreOrderIterator(argument) specifiers;
  BTPreOrderIterator(BTPreOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BTPreOrderIterator() specifiers;
  virtual ~BTPreOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTPreOrderIterator& operator=(const BTPreOrderIterator&);

  // Move assignment
  // type operator=(argument) specifiers;
  BTPreOrderIterator& operator=(BTPreOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTPreOrderIterator&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTPreOrderIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override;

  // type Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTPreOrderIterator& operator++() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTPreOrderIterator<Data> {
                                  // Must extend MutableIterator<Data>,
                                  //             BTPreOrderIterator<Data>

private:

  // ...

protected:

  // ...

  using BTPreOrderIterator<Data>::root;
  using BTPreOrderIterator<Data>::current;
  using BTPreOrderIterator<Data>::stack;

public:

  // Specific constructors
  // BTPreOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  BTPreOrderMutableIterator(const BinaryTree<Data>& binaryTree) : BTPreOrderIterator<Data>::BTPreOrderIterator(binaryTree) {}

  /* ************************************************************************ */

  // Copy constructor
  // BTPreOrderMutableIterator(argument) specifiers;
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator& iter) : BTPreOrderIterator<Data>::BTPreOrderIterator(iter){}

  // Move constructor
  // BTPreOrderMutableIterator(argument) specifiers;
  BTPreOrderMutableIterator(BTPreOrderMutableIterator&& iter) noexcept : BTPreOrderIterator<Data>::BTPreOrderIterator(std::move(iter)){}

  /* ************************************************************************ */

  // Destructor
  // ~BTPreOrderMutableIterator() specifiers;
  virtual ~BTPreOrderMutableIterator() {}

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator& iter) {
    BTPreOrderIterator<Data>::operator=(iter);
    return *this;
  }

  // Move assignment
  // type operator=(argument) specifiers;
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&& iter) noexcept {
    BTPreOrderIterator<Data>::operator=(std::move(iter));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTPreOrderMutableIterator&) const noexcept = default;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTPreOrderMutableIterator&) const noexcept = default;


  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (current!=nullptr) {
      return const_cast<Data&> (current->Element());
    } else {
      throw std::out_of_range("MutableIterator PreOrder has terminated");
    }
  }

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>, 
                            virtual public ResettableIterator<Data> {
                            // Must extend ForwardIterator<Data>,
                            //             ResettableIterator<Data>

private:

  // ...

protected:

  // ...

 // using typename BinaryTree<Data>::Node;

  typename BinaryTree<Data>::Node * current = nullptr;

  typename BinaryTree<Data>::Node * root = nullptr;

  typename BinaryTree<Data>::Node * last = nullptr;

  StackLst<typename BinaryTree<Data>::Node*> stack;

  

public:

  // Specific constructors
  // BTPostOrderIterator(argument) specifiers; // An iterator over a given binary tree
  BTPostOrderIterator(const BinaryTree<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // BTPostOrderIterator(argument) specifiers;
  BTPostOrderIterator(const BTPostOrderIterator&);

  // Move constructor
  // BTPostOrderIterator(argument) specifiers;
  BTPostOrderIterator(BTPostOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BTPostOrderIterator() specifiers;
  virtual ~BTPostOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTPostOrderIterator& operator=(const BTPostOrderIterator&);

  // Move assignment
  // type operator=(argument) specifiers;
  BTPostOrderIterator& operator=(BTPostOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTPostOrderIterator&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTPostOrderIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override;

  // type Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTPostOrderIterator& operator++() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override;

protected:

  void getCurrentMostLeftLeaf();

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>, 
                                   virtual public BTPostOrderIterator<Data>{
                                  // Must extend MutableIterator<Data>,
                                  //             BTPostOrderIterator<Data>

private:

  // ...

protected:

  // ...
  using BTPostOrderIterator<Data>::current;
  using BTPostOrderIterator<Data>::root;
  using BTPostOrderIterator<Data>::last;
  using BTPostOrderIterator<Data>::stack;

public:

  // Specific constructors
  // BTPostOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  BTPostOrderMutableIterator(const BinaryTree<Data>& binaryTree) : BTPostOrderIterator<Data>::BTPostOrderIterator(binaryTree) {}

  /* ************************************************************************ */

  // Copy constructor
  // BTPostOrderMutableIterator(argument) specifiers;
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator& iter) : BTPostOrderIterator<Data>::BTPostOrderIterator(iter){}

  // Move constructor
  // BTPostOrderMutableIterator(argument) specifiers;
  BTPostOrderMutableIterator(BTPostOrderMutableIterator&& iter) noexcept : BTPostOrderIterator<Data>::BTPostOrderIterator(std::move(iter)){}

  /* ************************************************************************ */

  // Destructor
  // ~BTPostOrderMutableIterator() specifiers;
  virtual ~BTPostOrderMutableIterator() {}

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator& iter) {
    BTPostOrderIterator<Data>::operator=(iter);
    return *this;
  }

  // Move assignment
  // type operator=(argument) specifiers;
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&& iter) noexcept {
    BTPostOrderIterator<Data>::operator=(std::move(iter));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTPostOrderMutableIterator&) const noexcept = default;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTPostOrderMutableIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (current!=nullptr) {
      return const_cast<Data&> (current->Element());
    } else {
      throw std::out_of_range("MutableIterator PostOrder has terminated");
    }
  }

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {
                          // Must extend ForwardIterator<Data>,
                          //             ResettableIterator<Data>

private:

  // ...

protected:

  // ...

  //using typename BinaryTree<Data>::Node;

  typename BinaryTree<Data>::Node * current = nullptr;

  typename BinaryTree<Data>::Node * root = nullptr;

  StackLst<typename BinaryTree<Data>::Node*> stack;

  

public:

  // Specific constructors
  // BTInOrderIterator(argument) specifiers; // An iterator over a given binary tree
  BTInOrderIterator(const BinaryTree<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // BTInOrderIterator(argument) specifiers;
  BTInOrderIterator(const BTInOrderIterator&);

  // Move constructor
  // BTInOrderIterator(argument) specifiers;
  BTInOrderIterator(BTInOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BTInOrderIterator() specifiers;
  virtual ~BTInOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTInOrderIterator& operator=(const BTInOrderIterator&);

  // Move assignment
  // type operator=(argument) specifiers;
  BTInOrderIterator& operator=(BTInOrderIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTInOrderIterator&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTInOrderIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override;

  // type Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTInOrderIterator& operator++() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override;

protected:
  void getCurrentMostLeftNode();

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>, 
                                 virtual public BTInOrderIterator<Data> {
                                  // Must extend MutableIterator<Data>,
                                  //             BTInOrderIterator<Data>

private:

  // ...

protected:

  // ...
  using BTInOrderIterator<Data>::root;
  using BTInOrderIterator<Data>::current;
  using BTInOrderIterator<Data>::stack;

public:

  // Specific constructors
  // BTInOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  BTInOrderMutableIterator(const BinaryTree<Data>& binaryTree) : BTInOrderIterator<Data>::BTInOrderIterator(binaryTree) {}

  /* ************************************************************************ */

  // Copy constructor
  // BTInOrderMutableIterator(argument) specifiers;
  BTInOrderMutableIterator(const BTInOrderMutableIterator& iter) : BTInOrderIterator<Data>::BTInOrderIterator(iter) {}

  // Move constructor
  // BTInOrderMutableIterator(argument) specifiers;
  BTInOrderMutableIterator(BTInOrderMutableIterator&& iter) noexcept : BTInOrderIterator<Data>::BTInOrderIterator(std::move(iter)) {}

  /* ************************************************************************ */

  // Destructor
  // ~BTInOrderMutableIterator() specifiers;
  virtual ~BTInOrderMutableIterator() {}

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator& iter) {
    BTInOrderIterator<Data>::operator=(iter);
    return *this;
  }

  // Move assignment
  // type operator=(argument) specifiers;
  BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&& iter) noexcept {
    BTInOrderIterator<Data>::operator=(std::move(iter));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTInOrderMutableIterator&) const noexcept = default;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTInOrderMutableIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (current!=nullptr) {
      return const_cast<Data&> (current->Element());
    } else {
      throw std::out_of_range("MutableIterator InOrder has terminated");
    }
  }

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {
                          // Must extend ForwardIterator<Data>,
                          //             ResettableIterator<Data>

private:

  // ...

protected:

  // ...

  //using typename BinaryTree<Data>::Node;

  typename BinaryTree<Data>::Node * current = nullptr;

  typename BinaryTree<Data>::Node * root = nullptr;

  QueueLst<typename BinaryTree<Data>::Node*> queue;

public:

  // Specific constructors
  // BTBreadthIterator(argument) specifiers; // An iterator over a given binary tree
  BTBreadthIterator(const BinaryTree<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  // BTBreadthIterator(argument) specifiers;
  BTBreadthIterator(const BTBreadthIterator&);

  // Move constructor
  // BTBreadthIterator(argument) specifiers;
  BTBreadthIterator(BTBreadthIterator&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~BTBreadthIterator() specifiers;
  virtual ~BTBreadthIterator();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTBreadthIterator& operator=(const BTBreadthIterator&);

  // Move assignment
  // type operator=(argument) specifiers;
  BTBreadthIterator& operator=(BTBreadthIterator&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTBreadthIterator&) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTBreadthIterator&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  const Data& operator*() const override;

  // type Terminated() specifiers; // (should not throw exceptions)
  bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  // type operator++() specifiers; // (throw std::out_of_range when terminated)
  BTBreadthIterator& operator++() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTBreadthIterator<Data> {
                                  // Must extend MutableIterator<Data>,
                                  //             BTBreadthIterator<Data>

private:

  // ...

protected:

  // ...
  using BTBreadthIterator<Data>::root;
  using BTBreadthIterator<Data>::current;
  using BTBreadthIterator<Data>::queue;

public:

  // Specific constructors
  // BTBreadthMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree
  BTBreadthMutableIterator(const BinaryTree<Data>& binaryTree) : BTBreadthIterator<Data>::BTBreadthIterator(binaryTree){}

  /* ************************************************************************ */

  // Copy constructor
  // BTBreadthMutableIterator(argument) specifiers;
  BTBreadthMutableIterator(const BTBreadthMutableIterator& iter) : BTBreadthIterator<Data>::BTBreadthIterator(iter){}

  // Move constructor
  // BTBreadthMutableIterator(argument) specifiers;
  BTBreadthMutableIterator(BTBreadthMutableIterator&& iter) noexcept : BTBreadthIterator<Data>::BTBreadthIterator(std::move(iter)){}

  /* ************************************************************************ */

  // Destructor
  // ~BTBreadthMutableIterator() specifiers;
  virtual ~BTBreadthMutableIterator() {}

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator& iter) {
    BTBreadthIterator<Data>::operator=(iter);
    return *this;
  }

  // Move assignment
  // type operator=(argument) specifiers;
  BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&& iter) noexcept {
    BTBreadthIterator<Data>::operator=(std::move(iter));
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const BTBreadthMutableIterator&) const noexcept = default;
  // type operator!=(argument) specifiers;
  bool operator!=(const BTBreadthMutableIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data& operator*() override {
    if (current!=nullptr) {
      return const_cast<Data&> (current->Element());
    } else {
      throw std::out_of_range("MutableIterator Breadth has terminated");
    }
  }

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
