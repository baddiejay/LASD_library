
namespace lasd {

/* ************************************************************************** */

// *********** NODE *****************

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data &newData) {
    data=newData;
    leftChild = nullptr;
    rightChild = nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data &&newData) noexcept {
    std::swap(data, newData);
    leftChild = nullptr;
    rightChild = nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    if(leftChild != nullptr) {
        delete leftChild;
        leftChild = nullptr;
    }

    if(rightChild != nullptr) {
        delete rightChild;
        rightChild = nullptr;  
    }
}

template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return data;
}

template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return data;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return (leftChild!=nullptr);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
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

    QueueLst<NodeLnk*> queue;

    container.Traverse([this, &queue](const Data &newData) {

        
        if (root==nullptr) {
            root = new NodeLnk(newData);
            queue.Enqueue(root);

        } else if (!queue.Empty()){

            if (queue.Head()->leftChild == nullptr) {

                queue.Head()->leftChild = new NodeLnk(newData);
                queue.Enqueue(queue.Head()->leftChild);

            } else {

                queue.Head()->rightChild = new NodeLnk(newData);
                queue.Enqueue(queue.Head()->rightChild);
                queue.Dequeue();
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
    
    NodeLnk* node = nullptr;

    if(copyNode!=nullptr){
        
        node = new NodeLnk(copyNode->data);

        if(copyNode->leftChild!=nullptr) {
            node->leftChild = recursiveCopyTree(copyNode->leftChild);
        }

        if(copyNode->rightChild!=nullptr) {
            node->rightChild = recursiveCopyTree(copyNode->rightChild);
        }
    }

    return node;
}

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
    
    if(binaryTreeLnk.size!=0) {
        
        BinaryTreeLnk<Data>* tmpBinaryTreeLnk = new BinaryTreeLnk<Data>(binaryTreeLnk);
	    
        std::swap(*tmpBinaryTreeLnk, *this);
	    
        delete tmpBinaryTreeLnk;

    } else{

        Clear();
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
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {

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
    
    delete root;
    
    root = nullptr;
}
/* ************************************************************************** */

}
