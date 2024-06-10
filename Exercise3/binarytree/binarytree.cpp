namespace lasd {

/* ************************************************************************** */

// *************************** NODE ***************************

/* This function checks whether the current nodes (this) and the node passed as parameter (node) are equal. 
Equality is determined not only by comparing the values contained in the nodes, but also by the structure 
of the tree starting with these nodes (i.e. their children).*/
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node &node) const noexcept {
    if (node.Element() == Element()){      //The data contained in the two nodes are compared.
        bool hasRChild = HasRightChild();  //It is checked whether each node has a left and right child for this and node
        bool hasLChild = HasLeftChild(); 

        bool otherHasRChild = node.HasRightChild();
        bool otherHasLChild = node.HasLeftChild(); 

        bool right = (hasRChild == otherHasRChild);
        bool left = (hasLChild == otherHasLChild); 

        //If both nodes have the same structure (both have or do not have left and right children), the children are compared recursively.
        if(left && right){ 
            if (hasLChild && hasRChild){
                return ((node.LeftChild() == LeftChild()) && (node.RightChild() == RightChild()));
            } else if (hasLChild) {
                return (node.LeftChild() == LeftChild());
            } else if (hasRChild) {
                return (node.RightChild() == RightChild());
            } else {
                return true;    //If none of the nodes have children, they are equal.
            }
        }
    }
  return false;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
}

template <typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
    return (!HasRightChild() && !HasLeftChild());
}

/* Since operator== for the nodes provides a detailed comparison between nodes in a binary tree 
(considering both the value contained in the nodes and the structure of the tree), 
I only need to start the comparison between the two roots*/
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data> &binaryTree) const noexcept {
    if (size == binaryTree.size) {
        if (size != 0) {
            return (Root() == binaryTree.Root());
        } else {
            return true;
        }
    } else {
        return false;
    }
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data> &binaryTree) const noexcept {
    return !(*this == binaryTree);
}

//******************** BINARY TREE *************************

template <typename Data>
void BinaryTree<Data>::Traverse(TraverseFun fun) const {
    if(!this->Empty()){
      PreOrderTraverse(fun, &Root());
    }
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const {
    if(!this->Empty()){
      PreOrderTraverse(fun, &Root());
    }
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun,  const Node * cur) const {
    if(cur != nullptr){    
        fun(cur->Element());
        if(cur->HasLeftChild()){
            PreOrderTraverse(fun, &(cur->LeftChild()));
        }
        if(cur->HasRightChild()) {
            PreOrderTraverse(fun, &(cur->RightChild()));
        }
    }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const {
    if(!this->Empty()){
      PostOrderTraverse(fun, &Root());
    }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun, const Node * cur) const {
    if(cur != nullptr){    
        if(cur->HasLeftChild()) {
            PostOrderTraverse(fun, &(cur->LeftChild()));
        }
        if(cur->HasRightChild()) {
            PostOrderTraverse(fun, &(cur->RightChild()));
        }
        fun(cur->Element());
    }
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const {
    if(!this->Empty()){
      InOrderTraverse(fun, &Root());
    }
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun fun, const Node* cur) const {
    if(cur != nullptr){    
        if(cur->HasLeftChild()){
            InOrderTraverse(fun,  &(cur->LeftChild()));
        }
        fun(cur->Element());
        if(cur->HasRightChild()){
            InOrderTraverse(fun, &(cur->RightChild()));
        }
    }
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const {
    if(!this->Empty()){
      BreadthTraverse(fun, &Root());
    }
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node* node) const {    
    QueueLst<const Node*> tmpQueue;
    tmpQueue.Enqueue(node);
    
    const Node* tmp;

    while(!(tmpQueue.Empty())){
        tmp = tmpQueue.HeadNDequeue();
        fun(tmp->Element());
        if(tmp->HasLeftChild()) {
            tmpQueue.Enqueue(&(tmp->LeftChild()));
        }
        if(tmp->HasRightChild()){
            tmpQueue.Enqueue(&(tmp->RightChild()));
        }
    }
}

// ********************* MUTABLE BINARY TREE *********************
template <typename Data>
void MutableBinaryTree<Data>::Map(MapFun fun) {
    PreOrderMap(fun, &Root());
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) {
    PreOrderMap(fun, &Root());
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun fun, MutableNode * cur)  {
    if(cur != nullptr){
        fun(cur->Element());
        if(cur->HasLeftChild()) {
            PreOrderMap(fun, &(cur->LeftChild()));
        }
        if(cur->HasRightChild()) {
            PreOrderMap(fun, &(cur->RightChild()));
        }
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) {
    PostOrderMap(fun, &Root());
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun fun, MutableNode * cur) {
    if(cur != nullptr){
        if(cur->HasLeftChild()) {
            PostOrderMap(fun, &(cur->LeftChild()));
        }
        if(cur->HasRightChild()) {
            PostOrderMap(fun, &(cur->RightChild()));
        }
        fun(cur->Element());
    }
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun fun) {
    InOrderMap(fun, &Root());
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun fun, MutableNode* cur) {    
    if(cur != nullptr){
        if(cur->HasLeftChild()){
            InOrderMap(fun,  &(cur->LeftChild()));
        }
        fun(cur->Element());
        if(cur->HasRightChild()){
            InOrderMap(fun, &(cur->RightChild()));
        }
    }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun fun) {
    BreadthMap(fun, &Root());
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun fun,  MutableNode* node) {    
    QueueLst<MutableNode*> tmpQueue;
    tmpQueue.Enqueue(node);
    
    MutableNode* tmp;
    
    while(!(tmpQueue.Empty())){    
        tmp = tmpQueue.HeadNDequeue();
        fun(tmp->Element());
        if(tmp->HasLeftChild()) {
            tmpQueue.Enqueue(&(tmp->LeftChild()));
        }
        if(tmp->HasRightChild()){
            tmpQueue.Enqueue(&(tmp->RightChild()));
        }
    }
}

// ********** PRE ORDER ITERATOR ************

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &binaryTree) {
    root = &binaryTree.Root();
    current = &binaryTree.Root();
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> &iter) {
    root = iter.root;
    current = iter.current;
    stack = iter.stack;
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data> &&iter) noexcept {
    std::swap(root, iter.root);
    std::swap(current,iter.current);
    stack = std::move(iter.stack);
}

template <typename Data>
BTPreOrderIterator<Data>::~BTPreOrderIterator() {
    stack.Clear();
    //They are just pointers, I don't allocate dynamic memory so I don't have to destroy
    current = nullptr;
    root = nullptr;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> &iter) {
    if(this != &iter){
      root = iter.root;
      current = iter.current;
      stack = iter.stack;
    }
    return *this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> &&iter) noexcept { 
    std::swap(root, iter.root);
    std::swap(current, iter.current); 
    stack = std::move(iter.stack);  
    return *this;
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> &iter) const noexcept {
    return (root==iter.root && current==iter.current && stack==iter.stack);
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

template <typename Data>
const Data& BTPreOrderIterator<Data>::operator*() const {    
    if(!Terminated()){
        return current->Element();
    } else {
        throw std::out_of_range("Iterator PreOrder has terminated");
    } 
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
    current = root;
    stack.Clear(); // Empty the iterator otherwise its state is inconsistent
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {    
    if(Terminated()){
        throw std::out_of_range("Iterator PreOrder has terminated.");
    }        
    if(current->HasRightChild()) {
        stack.Push(&(current->RightChild()));
    }       
    if(current->HasLeftChild()) {
        stack.Push(&(current->LeftChild()));
    }
    /* If the stack is empty, it means that there are no more nodes to visit, so current is set to nullptr 
    (the iterator has finished its traversal). Otherwise, the next node to visit is taken from the stack 
    (TopNPop()), which returns and removes the node at the top of the stack.  */    
    if(stack.Empty()){
        current = nullptr;
    } else {
        current = stack.TopNPop();
    }
            
    return *this;
}

// ********** BREADTH ITERATOR ************

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> &binaryTree) {
    root = &binaryTree.Root();
    current = &binaryTree.Root();
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data> &iter) {
    root = iter.root;
    current = iter.current;
    queue = iter.queue;
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> &&iter) noexcept {    
    std::swap(root,iter.root);
    std::swap(current,iter.current);    
    queue = std::move(iter.queue);
}

template <typename Data>
BTBreadthIterator<Data>::~BTBreadthIterator() {
    queue.Clear();
    current = nullptr;
    root = nullptr;    
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> &iter) {
    if(this != &iter){
      root = iter.root;
      current = iter.current;
      queue = iter.queue;   
    }
    return *this;
}


template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> &&iter) noexcept {  
    std::swap(root, iter.root);
    std::swap(current, iter.current); 
    queue = std::move(iter.queue); 
    return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> &iter) const noexcept {
    return (root==iter.root && current==iter.current && queue==iter.queue);
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

template <typename Data>
const Data& BTBreadthIterator<Data>::operator*() const {    
    if(!Terminated()){
        return current->Element();
    } else {
        throw std::out_of_range("Iterator Breadth has terminated");
    } 
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
    current = root;
    queue.Clear();
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {   
    if(Terminated()){
        throw std::out_of_range("Iterator Breadth has terminated.");
    }           
    if(current->HasLeftChild()) {       
        queue.Enqueue(&(current->LeftChild()));
    }          
    if(current->HasRightChild()) {       
        queue.Enqueue(&(current->RightChild()));
    }   
    if(queue.Empty()) {       
        current = nullptr;
    } else {
        current = queue.HeadNDequeue();
    }       
    return *this;
}

// ********** IN ORDER ITERATOR ************

template <typename Data>
void BTInOrderIterator<Data>::getCurrentMostLeftNode() {
    while (current->HasLeftChild()) { 
        stack.Push(current);
        current = &(current->LeftChild());
    }
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &binaryTree) { 
    root = &binaryTree.Root();
    current = &binaryTree.Root();
    getCurrentMostLeftNode();  // Sets the current to the leftmost node that is the first to be visited
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> &iter) {  
    root = iter.root;
    current = iter.current;
    stack = iter.stack;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> &&iter) noexcept { 
    std::swap(root, iter.root);
    std::swap(current,iter.current);  
    stack = std::move(iter.stack);
}

template <typename Data>
BTInOrderIterator<Data>::~BTInOrderIterator() {
    stack.Clear();
    current = nullptr;
    root = nullptr;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> &iter) {
    if(this != &iter){
      root = iter.root;
      current = iter.current;   
      stack = iter.stack;
    }
    return *this;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> &&iter) noexcept {    
    std::swap(root, iter.root);
    std::swap(current, iter.current);   
    stack = std::move(iter.stack);    
    return *this;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> &iter) const noexcept {
    return (root==iter.root && current==iter.current && stack==iter.stack);
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

template <typename Data>
const Data& BTInOrderIterator<Data>::operator*() const {   
    if(!Terminated()){
        return current->Element();
    } else {
        throw std::out_of_range("Iterator InOrder has terminated");
    } 
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept
{
    current = root;
    stack.Clear(); 
    if(current != nullptr) {
        getCurrentMostLeftNode(); // Unless the structure is finished, I have to start from the leftmost node
    }    
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {    
    if(Terminated()) {
        throw std::out_of_range("Iterator InOrder has terminated.");
    }      
    if(current->HasRightChild()){
        current = &(current->RightChild());
        getCurrentMostLeftNode();

    } else {
        if(stack.Empty()) {
            current = nullptr;
        } else {
            current = stack.TopNPop(); 
        }
    }
    return *this;
}

//******POST ORDER ITERATOR********

template <typename Data>
void BTPostOrderIterator<Data>::getCurrentMostLeftLeaf() {
    if(current==nullptr)
        return;   
    while (current->HasLeftChild()) {
        stack.Push(current);
        current = &(current->LeftChild());
    }
    if(current->HasRightChild()) {
        stack.Push(current);
        current = &(current->RightChild());
        getCurrentMostLeftLeaf();
    }
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> &binaryTree) {  
    root = &binaryTree.Root();
    current = &binaryTree.Root();  
    getCurrentMostLeftLeaf();  
    last = current;
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> &iter) {  
    root = iter.root;
    current = iter.current;  
    last = iter.last;    
    stack = iter.stack;
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> &&iter) noexcept {    
    std::swap(root,iter.root);
    std::swap(current,iter.current);   
    std::swap(last,iter.last);    
    stack = std::move(iter.stack);
}

template <typename Data>
BTPostOrderIterator<Data>::~BTPostOrderIterator() {
    stack.Clear();   
    current = nullptr;
    root = nullptr;
    last = nullptr;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> &iter) {
    if(this != &iter){
      root = iter.root;
      current = iter.current;   
      last = iter.last;   
      stack = iter.stack;
    }
    return *this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> &&iter) noexcept {    
    std::swap(root, iter.root);
    std::swap(current, iter.current);
    std::swap(last,iter.last);   
    stack = std::move(iter.stack);   
    return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> &iter) const noexcept {
    return (root==iter.root && current==iter.current && last==iter.last && stack==iter.stack);
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept
{
    current = root;   
    stack.Clear();
    if(current != nullptr) {
        getCurrentMostLeftLeaf();       
        last = current;
    }
}

template <typename Data>
const Data& BTPostOrderIterator<Data>::operator*() const {    
    if(!Terminated()){
        return current->Element();
    } else {
        throw std::out_of_range("Iterator PostOrder has terminated");
    } 
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {   
    if(Terminated()) {
        throw std::out_of_range("Iterator PostOrder has terminated.");
    }
    if(stack.Empty()){  //If the stack is empty, it means that the iterator has completed traversing the tree
        current = nullptr;
        last = nullptr;
    } else {
        current = stack.TopNPop();       
        if(current->HasRightChild() && !(&(current->RightChild())==last)){           
            stack.Push(current);
            current = &(current->RightChild());
            getCurrentMostLeftLeaf();

        }
    }
    last = current;
  
    return *this;
}
/* ************************************************************************** */

}
