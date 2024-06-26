
namespace lasd {

/* ************************************************************************** */

// *********** NODE *****************

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data &newData) : data(newData), leftChild(nullptr), rightChild(nullptr) {}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data &&newData) noexcept : data(std::move(newData)), leftChild(nullptr), rightChild(nullptr){}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete leftChild;
    leftChild = nullptr;
    
    delete rightChild;
    rightChild = nullptr;
}

template <typename Data>
inline const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return data;
}

template <typename Data>
inline Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return data;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return (leftChild!=nullptr);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return (rightChild!=nullptr);
}

template <typename Data>
const BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if(!HasLeftChild()) {
        throw std::out_of_range("No left child");
    }
    return *leftChild;
}

template <typename Data>
const BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const { 
    if(!HasRightChild()) {
        throw std::out_of_range("No right child");
    }
    return *rightChild;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() {
    if(!HasLeftChild()) {
        throw std::out_of_range("No left child");
    }
    return *leftChild;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() {
    if(!HasRightChild()) {
        throw std::out_of_range("No right child");
    }
    return *rightChild;
}

//*********** BINARY TREE **************

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> & container) {
    size = container.Size();
    QueueLst<NodeLnk*> queue;	//Use a queue to keep track of nodes that have yet to receive children

    container.Traverse([this, &queue](const Data &newData) {
        if (root==nullptr) {	//If the tree is empty, this is the root
            root = new NodeLnk(newData);
            queue.Enqueue(root);
        } else if (!queue.Empty()){
            if (queue.Head()->leftChild == nullptr) {
                queue.Head()->leftChild = new NodeLnk(newData);
                queue.Enqueue(queue.Head()->leftChild);
            } else {
                queue.Head()->rightChild = new NodeLnk(newData);
                queue.Enqueue(queue.Head()->rightChild);
                queue.Dequeue();  //The head node is removed from the tail since both its children are now assigned.
            }
        }

    });
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> && container) noexcept{
    std::swap(size, container.Size());
    QueueLst<NodeLnk*> queue;

    container.Map([this, &queue](Data &newData) {
        if (root==nullptr) {
            root = new NodeLnk(std::move(newData));
            queue.Enqueue(root);
        } else if (!queue.Empty()){
            if (queue.Head()->leftChild == nullptr) {
                queue.Head()->leftChild = new NodeLnk(std::move(newData));
                queue.Enqueue(queue.Head()->leftChild);
            } else {
                queue.Head()->rightChild = new NodeLnk(std::move(newData));
                queue.Enqueue(queue.Head()->rightChild);
                queue.Dequeue();
            }
        }
    });
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    Clear();
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::recursiveCopyTree(NodeLnk * copyNode) {
    if (copyNode == nullptr) return nullptr;

    NodeLnk* newNode = new NodeLnk(copyNode->data);
    newNode->leftChild = recursiveCopyTree(copyNode->leftChild);
    newNode->rightChild = recursiveCopyTree(copyNode->rightChild);
    return newNode;
}

// Members of the base class must be initialized in the constructor body of the derived class, not in the initialization list of the constructor of the derived class
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> &binaryTreeLnk) {
    size=binaryTreeLnk.size;
    if (size>0) {
        root = recursiveCopyTree(binaryTreeLnk.root);
    }
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> &&binaryTreeLnk) noexcept {
    std::swap(root,binaryTreeLnk.root);
    std::swap(size,binaryTreeLnk.size);
}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> &binaryTreeLnk) {
// The recursiveCopyTree function recursively copies the tree nodes, creating a new structure identical to the source tree while avoiding an additional call to new and delete, which can be costly in terms of performance and introduces additional complexity.
    if (this != &binaryTreeLnk) {
        Clear();
        root = recursiveCopyTree(binaryTreeLnk.root);
        size = binaryTreeLnk.size;
    }
    return *this;
}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> &&binaryTreeLnk) noexcept {
    std::swap(root,binaryTreeLnk.root);
    std::swap(size,binaryTreeLnk.size);
    return *this;
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data> &binaryTreeLnk) const noexcept {
    return BinaryTree<Data>::operator==(binaryTreeLnk);
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data> &binaryTreeLnk) const noexcept {
    return !(*this == binaryTreeLnk);
}

template <typename Data>
const BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if(root==nullptr) {
        throw std::length_error("Empty BinaryTreeLnk");
    }
    return *root;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() {
    if(root==nullptr) {
        throw std::length_error("Empty BinaryTreeLnk");
    }
    return *root;
}

template <typename Data>
void BinaryTreeLnk<Data>::Clear() noexcept {
    size=0;
    delete root; //It deallocates the entire tree, as NodeLnk's destructor takes care of deallocating the children.
    root = nullptr;
}
/* ************************************************************************** */

}
