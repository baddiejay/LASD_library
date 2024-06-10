
namespace lasd {

/* ************************************************************************** */

template <typename Data>
BST<Data>::BST(const TraversableContainer<Data> & container) {
    container.Traverse([this] (const Data& newData){
        Insert(newData);
    });
}

template <typename Data>
BST<Data>::BST(MappableContainer<Data> && container) noexcept{
    container.Map([this] (Data& newData){
        Insert(std::move(newData));
    });
}

template <typename Data>
BST<Data>::BST(const BST<Data> &bst) : BinaryTreeLnk<Data>(bst) {}

template <typename Data>
BST<Data>::BST(BST<Data> &&bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)) {}

template <typename Data>
BST<Data>& BST<Data>::operator=(const BST &bst) {
    BinaryTreeLnk<Data>::operator=(bst);
    return *this;
}

template <typename Data>
BST<Data>& BST<Data>::operator=(BST &&bst) noexcept {
    BinaryTreeLnk<Data>::operator=(std::move(bst));
    return *this;
}

template <typename Data>
bool BST<Data>::operator==(const BST &bst) const noexcept {    
    if(size!=bst.size){
        return false;   
    } else if(size==0) {        
        return true;               
    } else {
        BTInOrderIterator<Data> iter(*this);
        BTInOrderIterator<Data> iterOther(bst);
        
        while (!iter.Terminated() && !iterOther.Terminated()){            
            if(*iter != *iterOther) {
                return false;
            }
            ++iter;
            ++iterOther;
        }

        return (iter.Terminated() && iterOther.Terminated());
    }
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST &bst) const noexcept {
    return !(*this == bst);
}

//****************** SPECIFIC MEMBER FUNCTIONS **************** 
template <typename Data>
const Data& BST<Data>::Min() const { 
    if(root==nullptr) {
        throw std::length_error("Empty BST.");
    }

    return FindPointerToMin(root)->data;
}

template <typename Data>
Data BST<Data>::MinNRemove() {
    if(root==nullptr) {
        throw std::length_error("Empty BST.");
    }
   
    return DataNDelete(DetachMin(root));
}

template <typename Data>
void BST<Data>::RemoveMin() {
    if(root==nullptr) {
        throw std::length_error("Empty BST.");
    }

    delete DetachMin(root);    
}

template <typename Data>
const Data& BST<Data>::Max() const {   
    if(root==nullptr) {
        throw std::length_error("Empty BST.");
    }
    
    return FindPointerToMax(root)->data;
}

template <typename Data>
Data BST<Data>::MaxNRemove() { 
    if(root==nullptr) {
        throw std::length_error("Empty BST.");
    }
    
    return DataNDelete(DetachMax(root));
}

template <typename Data>
void BST<Data>::RemoveMax() {   
    if(root==nullptr) {
        throw std::length_error("Empty BST.");
    }
    
    delete DetachMax(root);
}

template <typename Data>
bool BST<Data>::Exists(const Data &searchData) const noexcept {
    return (FindPointerTo(root,searchData)!=nullptr);
}

template <typename Data>
bool BST<Data>::Insert(const Data &insertData) {  
    BST<Data>::NodeLnk*& pointer = FindPointerTo(root, insertData);
    
    if(pointer==nullptr) {
        pointer = new BST<Data>::NodeLnk(insertData);     
        size++;
        return true;
    } else {
        return false;
    }
}

template <typename Data>
bool BST<Data>::Insert(Data && moveData) noexcept {    
    BST<Data>::NodeLnk*& pointer = FindPointerTo(root, moveData);
    
    if(pointer==nullptr) {
        pointer = new BST<Data>::NodeLnk(std::move(moveData));       
        size++;
        return true;
    } else {
        return false;
    }
}

template <typename Data>
bool BST<Data>::Remove(const Data &removeData) noexcept {   
    BST<Data>::NodeLnk*& pointer = FindPointerTo(root, removeData);
    
    if(pointer!=nullptr) {
        delete Detach(pointer);       
        return true;
    } else {
        return false;
    }
}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data &predecessorData) const {
    const BST<Data>::NodeLnk* const* pointer = FindPointerToPredecessor(root, predecessorData);
    
    if(pointer==nullptr) {
        throw std::length_error("No Predecessor");
    }

    return (*pointer)->data;   
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data &predecessorData) {   
    BST<Data>::NodeLnk ** pointer = FindPointerToPredecessor(root, predecessorData);

    if(pointer==nullptr) {
        throw std::length_error("No Predecessor");
    }
    
    return DataNDelete(Detach(*pointer));
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data &predecessorData) {    
    BST<Data>::NodeLnk** pointer = FindPointerToPredecessor(root, predecessorData);
    
    if(pointer==nullptr) {
        throw std::length_error("No Predecessor");
    }
    
    delete Detach(*pointer);
}

template <typename Data>
const Data& BST<Data>::Successor(const Data &successorData) const {   
    const BST<Data>::NodeLnk* const* pointer = FindPointerToSuccessor(root, successorData);
    
    if(pointer==nullptr) {
        throw std::length_error("No Successor");
    }

    return (*pointer)->data;
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data &successorData) {   
    BST<Data>::NodeLnk** pointer = FindPointerToSuccessor(root, successorData);
    
    if(pointer==nullptr) {
        throw std::length_error("Successor not found.");
    }

    return DataNDelete(Detach(*pointer));
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data &successorData) {    
    BST<Data>::NodeLnk** pointer = FindPointerToSuccessor(root, successorData);
    
    if(pointer==nullptr) {
        throw std::length_error("No Successor");
    }

    delete Detach(*pointer);
}

//****************** AUXILIARY MEMBER FUNCTIONS ****************
template <typename Data>
Data BST<Data>::DataNDelete(BST<Data>::NodeLnk * node) {   
    Data extractedData;
    std::swap(extractedData, node->data);  
    delete node;   
    return extractedData;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk *&node) noexcept {   
    if (node!=nullptr) {
        if (node->leftChild == nullptr) {
            return Skip2Right(node);
        } else if (node->rightChild == nullptr) {
            return Skip2Left(node)
        } else {         
            NodeLnk* detach = DetachMax(node->leftChild);
            
            std::swap(node->data, detach->data);
            
            return detach; 
        }
    }
    return nullptr;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk *&node) noexcept {
    return Skip2Right(FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk *&node) noexcept {
    return Skip2Left(FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk * &node) noexcept {   
    NodeLnk* skipLeft = nullptr;
    
    if(node!=nullptr){
        std::swap(skipLeft,node->leftChild);      
        std::swap(skipLeft,node);      
        size--;
    }

    return skipLeft;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk * &node) noexcept {  
    NodeLnk* skipRight = nullptr;
    
    if(node!=nullptr){
        std::swap(skipRight,node->rightChild);     
        std::swap(skipRight,node);       
        size--;
    }

    return skipRight;
}

template <typename Data>
const typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(const NodeLnk* const& node) const noexcept {  
    if (node!=nullptr) {  
        if (node->HasLeftChild()) {
            return FindPointerToMin(node->leftChild);
        }
    }
        
    return node;
}


template <typename Data>
const typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(const NodeLnk* const & node) const noexcept {   
    if (node!=nullptr) {
        if (node->HasRightChild()) {
            return FindPointerToMax(node->rightChild);
        }
    }

    return node;
}


template <typename Data>
const typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(const NodeLnk* const &node, const Data& dataSearch) const noexcept {   
    if (node != nullptr) {
        if (node->Element() < dataSearch) {
            return FindPointerTo(node->rightChild, dataSearch);
        }
        if (node->Element() > dataSearch) {
            return FindPointerTo(node->leftChild, dataSearch);
        }
    }
    
    return node;
}


template <typename Data>
const typename BST<Data>::NodeLnk*const* BST<Data>::FindPointerToPredecessor(const NodeLnk* const & node, const Data& predecessorData) const noexcept {   
    if (node==nullptr) {
        return nullptr;
    }
    
    const NodeLnk* const * ptrToCurrent = &node;
    const NodeLnk* const * ptrToLeftParent = nullptr;
    
    while (true) {
        if ((*ptrToCurrent)->Element() < predecessorData) {           
            if ((*ptrToCurrent)->HasRightChild()) {
                ptrToLeftParent = ptrToCurrent;
                ptrToCurrent = &((*ptrToCurrent)->rightChild);
            } else {
                return ptrToCurrent;
            }
        } else if ((*ptrToCurrent)->Element() >= predecessorData) {
            if ((*ptrToCurrent)->HasLeftChild()) {
                ptrToCurrent = &((*ptrToCurrent)->leftChild);
            } else {
                return ptrToLeftParent;
            } 
        }
    }
}

template <typename Data>
const typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(const NodeLnk*const &node, const Data& successorData) const noexcept {   
    if(node == nullptr) {
        return nullptr;
    }       
    
    const NodeLnk* const * ptrToCurrent = &node;
    const NodeLnk* const * ptrToRightParent = nullptr;
    
    while (true) {
        if ((*ptrToCurrent)->Element() <= successorData) {           
            if ((*ptrToCurrent)->HasRightChild()) {
                ptrToCurrent = &((*ptrToCurrent)->rightChild);
            } else {
                return ptrToRightParent;
            } 
        } else if ((*ptrToCurrent)->Element() > successorData) {            
            if ((*ptrToCurrent)->HasLeftChild()) {              
                ptrToRightParent = ptrToCurrent;
                ptrToCurrent = &((*ptrToCurrent)->leftChild);
            } else {
                return ptrToCurrent;
            }
        }
    }
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(BST<Data>::NodeLnk*& node) noexcept {
    return const_cast<BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(BST<Data>::NodeLnk*& node) noexcept {
    return const_cast<BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(BST<Data>::NodeLnk*& node, const Data& dato) noexcept {
    return const_cast<BST<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, dato));
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(BST<Data>::NodeLnk*& node, const Data &dato) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, dato));
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(BST<Data>::NodeLnk*& node, const Data &dato) noexcept {
    return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, dato));
}

/* ************************************************************************** */

}
