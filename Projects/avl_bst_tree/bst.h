#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);


protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2);

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void deleteBST(Node<Key, Value>* &root);
    void removeLeaf(Node<Key, Value>* toRemove);
    void removeOneChild(Node<Key, Value>* toRemove);
    bool checkHeight(Node<Key, Value>* &current, int &height) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{

    return !(current_ == rhs.current_);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    current_ = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear(); // uses the clear funtion to deallocate all nodes;
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{

    //  if the tree is empty create a new node and set the trees root as the new node
    if(root_ == nullptr){
        Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        root_ = newNode;
        return;
    }

    // Retrieves a copy of the root for traversal
    Node<Key, Value>* temp = root_;

    while(temp->getKey() != keyValuePair.first){
        //  sets the value to compare
        Key compare = temp->getKey();

        //  if the right leaf node is null and the value is bigger, create a new node and slide it in BST
        if((temp->getRight() == nullptr) && (keyValuePair.first > compare)){
            Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
            temp->setRight(newNode);
            return;
        }
        //  if the left leaf node is null and the value is smaller, create a new node and slide it in BST
        else if((temp->getLeft() == nullptr) && (keyValuePair.first < compare)){
            Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
            temp->setLeft(newNode);
            return;
        }

        //  if the current node has no leaves possible go down the tree
        //  if the value is smaller go left, else larger go right
        if(keyValuePair.first < compare){
            temp = temp->getLeft();
        }
        else{
            temp = temp->getRight();
        }
    }
    temp->setValue(keyValuePair.second);
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{

    //  find if the key exists if not do nothing
    Node<Key, Value>* toRemove_ = internalFind(key);
    if(toRemove_ == nullptr) return;
    else{

        //leaf node case
        if((toRemove_->getLeft() == nullptr) && (toRemove_->getRight() == nullptr)){
            removeLeaf(toRemove_);
        }
        //  two children
        else if((toRemove_->getLeft() != nullptr) && (toRemove_->getRight() != nullptr)){

            // swap with predecessor so can be removed in lead or onechild case
            nodeSwap(predecessor(toRemove_), toRemove_);
            if(toRemove_->getRight() == nullptr && toRemove_->getLeft() == nullptr){
                removeLeaf(toRemove_);
            }
            else{
                removeOneChild(toRemove_);
            }
            return;
        }
        // one children
        else{
            removeOneChild(toRemove_);
        }
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeLeaf(Node<Key, Value>* toRemove){
    
   Node<Key, Value>* parent = toRemove->getParent();
    if(parent == nullptr){ //   if no parent then it must be a root node, need to set root to null
        root_ = nullptr;
    }
    else{
        if(parent->getRight() == toRemove){ //  find which side of the parent should be null
            parent->setRight(nullptr);
        }
        else{
            parent->setLeft(nullptr);
        }
    }

    delete toRemove;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeOneChild(Node<Key, Value>* toRemove){
    
    Node<Key, Value>* toMove;
    Node<Key, Value>* parent = toRemove->getParent();

    //  finds whehter the left or right node exists
    if(toRemove->getLeft() != nullptr){
        toMove = toRemove->getLeft();
        parent = toRemove->getParent();
    }
    else{
        toMove = toRemove->getRight();
        parent = toRemove->getParent();
    }

    if(parent == nullptr){ //    if theres no parent then the root must change
        root_ = toMove;
        toMove->setParent(nullptr);
        delete toRemove;
        return;
    }
    //  Finds where the existing node should be added to its parent
    if(parent->getRight() == toRemove){
        parent->setRight(toMove);
        toMove->setParent(parent);
    }
    else{
        parent->setLeft(toMove);
        toMove->setParent(parent);
    }

    delete toRemove;
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    //  The next smallest value in the tree

    //  If left is empty we must trace upward until tracing goes right
    if(current->getLeft() == nullptr){
        while(true){
            if(current->getParent() == nullptr) return nullptr;
            if(current == (current->getParent())->getRight()){
                return current->getParent();
            }
            current = current->getParent();
        }
    }
    else{

        //  trace once to the left, the smaller part then go down right until the end the largest in smaller part
        current = current->getLeft();
        while(current->getRight() != nullptr){
            current = current->getRight();
        }
    }

    return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    //  The next largest value in the tree

    //  If right is empty we must trace upward until tracing goes left
    if(current->getRight() == nullptr){
        while(true){
            if(current->getParent() == nullptr) return nullptr;
            if(current == (current->getParent())->getLeft()){
                return current->getParent();
            }
            current = current->getParent();
        }
    }
    else{

        //  trace once to the right, the smaller part then go down left until the end the smallest in larger part
        current = current->getRight();
        while(current->getLeft() != nullptr){
            current = current->getLeft();
        }
    }

    return current;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    //  calls the deleteBST helper function
    deleteBST(root_);
}

// Recursive function to delete a given binary tree
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteBST(Node<Key, Value>* &root)
{
    // empty tree
    if (root == nullptr) {
        return;
    }

    Node<Key, Value>* right = root->getRight();
    Node<Key, Value>* left = root->getLeft();

    // delete left and right subtree first
    deleteBST(left);
    deleteBST(right);
 
    // deletes the current node after deleting left and right subtree
    delete root;
    root = nullptr;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    //  Retrieves a copy of the root for traversal
    Node<Key, Value>* temp = root_;
    if(temp == nullptr) return nullptr;
    
    //  since the left will always have the smallest value, keep recursing left until hits nullptr
    while(temp->getLeft() != nullptr){
        temp = temp->getLeft();
    }

    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    //  Retrieves a copy of the root for traversal
    Node<Key, Value>* temp = root_;
    
    //  While beyond leaf node, or else the Key does not exist return nullptr
    while(temp != nullptr){

        //  If the key is the same return the temp pointer
        if(temp->getKey() == key){
            return temp;
        }

        //  if the key isnt the same traverse right if the key is smaller
        //  else larger traverse left
        if(temp->getKey() < key){
            temp = temp->getRight();
        }
        else{
            temp = temp->getLeft();
        }
    }

    return nullptr;

}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    Node<Key, Value>* temp = root_;
    int h = 0;
    if(root_ == nullptr){
        return true;
    }

    return checkHeight(temp, h);
}

// Recursive function to delete a given binary tree
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::checkHeight(Node<Key, Value>* &current, int &height) const
{
    int leftHeight = 0;
    int rightHeight = 0;
 
    //  l is true iff left subtree is true
    //  r is true iff right subtree is true
    int l = 0;
    int r = 0;
 
    if(current == nullptr){
        height = 0;
        return 1;
    }
 
    //  using recursive calls to obtain left and right subtree heights
    Node<Key, Value>* left = current->getLeft();
    Node<Key, Value>* right = current->getRight();
    l = checkHeight(left, leftHeight);
    r = checkHeight(right, rightHeight);
 
    //  the height of a subtree is the max of the left or right subtree plus 1
    if(leftHeight > rightHeight){
        height = leftHeight + 1;
    }
    else{
        height = rightHeight + 1;
    }
 
    //  if difference is more than one then the tree is not balanced
    //  we return zero because anything anded with zero will always be false
    //  the false will continue until it reaches back into the isBalanced function
    if (abs(leftHeight - rightHeight) >= 2) return 0;
    else return l && r; //  else it is true
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
