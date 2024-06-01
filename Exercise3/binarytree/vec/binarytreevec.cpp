namespace lasd {

/* ************************************************************************** */

// ******** NODE ******


template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data & newData, ulong newIndex, Vector<NodeVec*> *vec) {
    
    data = newData;
    index = newIndex;
    tree = vec;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& newData, ulong newIndex, Vector<NodeVec*> *vec) {
    
    std::swap(data, newData);
    index = newIndex;
    tree = vec;
}

template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return data;
}

template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return data;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return (index*2+1) <= (tree->Size() - 1);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
   return (index*2+2) <= (tree->Size() - 1);
}


template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    
    if(!HasLeftChild()) {
        throw std::out_of_range("No left child");
    }

    return *(tree->operator[](index*2+1));
}


template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
   
    if(!HasRightChild()) {
        throw std::out_of_range("No right child");
    }

    return *(tree->operator[](index*2+2));
}


template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    
    if(!HasLeftChild()) {
        throw std::out_of_range("No left child");
    }

    return *(tree->operator[](index*2+1));
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() {
   
    if(!HasRightChild()) {
        throw std::out_of_range("No right child");
    }

    return *(tree->operator[](index*2+2));
}

//**************** TREE ******************

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data> & container) {

    size = container.Size();

    vectorTree = new Vector<NodeVec*>(size);
    
    ulong i = 0;
    
    container.Traverse([this, &i](const Data &newData) {
            
            NodeVec* node = new NodeVec(newData, i, vectorTree);
            
            vectorTree->operator[](i) = node; 
            
            i++; 
        }
    );
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> && container) noexcept{

    std::swap(size, container.Size());

    vectorTree = new Vector<NodeVec*>(size);
    
    ulong i = 0;
    
    container.Map([this, &i](Data &newData) {
            
            NodeVec* node = new NodeVec(std::move(newData), i, vectorTree);
            
            vectorTree->operator[](i) = node; 
            
            i++; 
        }
    );
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &binaryTreeVec) {
    
    size = binaryTreeVec.size;
    
    vectorTree = new Vector<NodeVec*>(size);
    
    for(ulong i = 0; i<size; i++){
        
        NodeVec* node = new NodeVec(binaryTreeVec.vectorTree->operator[](i)->Element(),i,vectorTree);
        
        vectorTree->operator[](i) = node;
    }
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&binaryTreeVec) noexcept {

    std::swap(size,binaryTreeVec.size);
    std::swap(vectorTree,binaryTreeVec.vectorTree);
}

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
    
    Clear();

    delete vectorTree;

    vectorTree = nullptr;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> &binaryTreeVec) {
    
    BinaryTreeVec<Data>* tmpBinaryTreeVec = new BinaryTreeVec<Data>(binaryTreeVec);
	
    std::swap(*this,*tmpBinaryTreeVec);
	
    delete tmpBinaryTreeVec;
    
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> &&binaryTreeVec) noexcept {
    
    std::swap(size,binaryTreeVec.size);
    std::swap(vectorTree,binaryTreeVec.vectorTree);
    
    return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> &binaryTreeVec) const noexcept {
   return BinaryTree<Data>::operator==(binaryTreeVec);
}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> &binaryTreeVec) const noexcept{
    return !(*this == binaryTreeVec);
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    
    if(size==0) {
        throw std::length_error("Empty BinaryTreeVec");
    }

    return *(vectorTree->operator[](0));
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    
    if(size==0) {
        throw std::length_error("Empty BinaryTreeVec");
    }

    return *(vectorTree->operator[](0));
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(const TraverseFun fun) const {
    
    for(ulong i = 0; i < size; i++) {
        fun(vectorTree->operator[](i)->Element());
    }
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun fun){
    
    for(ulong i = 0; i < size; i++) {
        fun(vectorTree->operator[](i)->Element());
    }
}


template <typename Data>
void BinaryTreeVec<Data>::Clear() noexcept {
    
    if(size > 0) {

        for(ulong i = 0; i < size; i++) {
            delete (*vectorTree)[i];
        }

        vectorTree->Clear();
        size = 0;
    }
}
/* ************************************************************************** */

}
