#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}
/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item);
    virtual void remove(const Key& key);
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    bool isZigZig (AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key,Value>* c);
    void rotateLeft( AVLNode<Key,Value>* n);
    void rotateRight( AVLNode<Key,Value>* n);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current);
    void fixZigZig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p);
    void fixBalance(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* c, bool isRight);
    char updateParent(AVLNode<Key, Value>* p, AVLNode<Key, Value>* c);
    void removeFix(AVLNode<Key, Value>* current, char diff);
    void removalBalance(AVLNode<Key, Value>* n1, AVLNode<Key, Value>*n2, AVLNode<Key, Value>*n3, bool isRight);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    //  empty tree case
    if(this->root_ == nullptr){
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        this->root_ = newNode;
        return;
    }

    // Retrieves a copy of the root for traversal
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);

    while(temp->getKey() != new_item.first){
        //  sets the value to compare
        Key compare = temp->getKey();

        //  if the right leaf node is null and the value is bigger, create a new node and slide it in BST
        if((temp->getRight() == nullptr) && (new_item.first > compare)){
            AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
            temp->setRight(newNode);
            temp->updateBalance(1); //  adds one to the parent's balance since right is getting heavier
            if(temp->getBalance()) insertFix(temp, newNode); // if balance is not 0 then call insert fix
            return;
        }
        //  if the left leaf node is null and the value is smaller, create a new node and slide it in BST
        else if((temp->getLeft() == nullptr) && (new_item.first < compare)){
            AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
            temp->setLeft(newNode);
            temp->updateBalance(-1); // substracts one to the parent's balance since left is getting heavier
            if(temp->getBalance()) insertFix(temp, newNode); // if balance is not 0 then call insert fix
            return;
        }

        //  if the current node has no leaves possible go down the tree
        //  if the value is smaller go left, else larger go right
        if(new_item.first < compare){
            temp = temp->getLeft();
        }
        else{
            temp = temp->getRight();
        }
    }
    temp->setValue(new_item.second);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    //  find if the key exists if not do nothing
    AVLNode<Key, Value>* toRemove_ = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    AVLNode<Key, Value>* parent;
    char diff;
    if(toRemove_ == nullptr) return;
    else{
        parent = toRemove_->getParent();
        //leaf node case
        if((toRemove_->getLeft() == nullptr) && (toRemove_->getRight() == nullptr)){
            diff = updateParent(parent, toRemove_);
            this->removeLeaf(toRemove_);
        }
        //  two children
        else if((toRemove_->getLeft() != nullptr) && (toRemove_->getRight() != nullptr)){

            // swap with predecessor so can be removed in lead or onechild case
            nodeSwap(static_cast<AVLNode<Key, Value>*>(this->predecessor(toRemove_)), toRemove_);
            parent = toRemove_->getParent();
            if(toRemove_->getRight() == nullptr && toRemove_->getLeft() == nullptr){
                diff = updateParent(parent, toRemove_);
                this->removeLeaf(toRemove_);
            }
            else{
                diff = updateParent(parent, toRemove_);
                this->removeOneChild(toRemove_);
            }
        }
        // one children
        else{
            diff = updateParent(parent, toRemove_);
            this->removeOneChild(toRemove_);
        }
        removeFix(parent, diff);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* current, char diff){
    if(current == nullptr) return;
    current->updateBalance(diff);
    AVLNode<Key, Value>* parent = current->getParent();
    char ndiff = updateParent(parent, current);
    if(diff == char(-1)){   //  case when diff = -1
        if(current->getBalance() == char(-1)) return;
        else if(current->getBalance() == char(0)) removeFix(parent, ndiff);
        else{
            //  fetches the balances of the leftChild to see if its zigzig or zigzag
            AVLNode<Key, Value>* leftChild = current->getLeft();
            char leftBalance = leftChild->getBalance();
            if(leftBalance == char(-1)){
                rotateRight(current);
                current->setBalance(0);
                leftChild->setBalance(0);
                removeFix(parent, ndiff);
            }
            else if(leftBalance == char(1)){
                AVLNode<Key, Value>* rightChild = leftChild->getRight();
                rotateLeft(leftChild);
                rotateRight(current);
                removalBalance(current, leftChild, rightChild, 0);
                removeFix(parent,ndiff);
            }
            else{
                rotateRight(current);
                current->setBalance(-1);
                leftChild->setBalance(1);
            }
        }   
    }
    else if(diff == char(1)){   //  case when diff = 1
        if(current->getBalance() == char(1)) return;
        else if(current->getBalance() == char(0)) removeFix(parent, ndiff);
        else{
            //  fetches the balances of the rightChild to see if its zigzig or zigzag
            AVLNode<Key, Value>* rightChild = current->getRight();
            char rightBalance = rightChild->getBalance();
            if(rightBalance == char(1)){
                rotateLeft(current);
                current->setBalance(0);
                rightChild->setBalance(0);
                removeFix(parent, ndiff);
            }
            else if(rightBalance == char(-1)){
                AVLNode<Key, Value>* leftChild = rightChild->getLeft();
                rotateRight(rightChild);
                rotateLeft(current);
                removalBalance(current, rightChild, leftChild, 1);
                removeFix(parent,ndiff);
            }
            else{
                rotateLeft(current);
                current->setBalance(1);
                rightChild->setBalance(-1);
            }
        }
    }

}

template<class Key, class Value>
char AVLTree<Key, Value>::updateParent(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current){

    if(parent == nullptr) return 0; //    if the remove node was a root, nothing to be done above
    if(parent->getLeft() == current) return 1; //   if on the left needs to add because right will get heavy
    else return -1; //  else on the right after removal left will be heavy
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current){
    if(parent == nullptr) return;
    AVLNode<Key, Value>* grandParent = parent->getParent();
    if(grandParent == nullptr) return;
    //  the right version is a mirror of the left version with left/right and -/+ swaps
    if(parent == grandParent->getLeft()){   //  when the parent node is left of grandparent
        grandParent->updateBalance(-1);
        if(grandParent->getBalance() == char(0)) return;
        else if(grandParent->getBalance() == char(-1)) insertFix(grandParent, parent);
        else{
            if(isZigZig(grandParent, parent, current)){
                rotateRight(grandParent);
                fixZigZig(grandParent, parent);
            }
            else{
                rotateLeft(parent);
                rotateRight(grandParent);
                fixBalance(grandParent,parent,current,false);
            }
        }
    }
    else{   //  when the parent node is right of the grandparent
        grandParent->updateBalance(1);
        if(grandParent->getBalance() == char(0)) return;
        else if(grandParent->getBalance() == char(1)) insertFix(grandParent, parent);
        else{
            if(isZigZig(grandParent, parent, current)){
                rotateLeft(grandParent);
                fixZigZig(grandParent, parent);
            }
            else{
                rotateRight(parent);
                rotateLeft(grandParent);
                fixBalance(grandParent,parent,current,true);
            }
        }
    }
}

//  finds the pattern, if zigzig return true else return false for zigzag
template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZig (AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key,Value>* c){
    if(g->getLeft() == p && p->getLeft() == c) return true;
    else if(g->getRight() == p && p->getRight() == c) return true;
    return false;
}

//  rotates the node right
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* toRotate = n->getLeft();
    AVLNode<Key,Value>* grandParent = n->getParent();
    if(grandParent != nullptr){
        if(grandParent->getLeft() == n) grandParent->setLeft(toRotate);
        else grandParent->setRight(toRotate);
    }
    else{
        this->root_ = toRotate; // if the grandparent of the parent doesn't exist then root must be parent
    }
    //  swapping pointers
    toRotate->setParent(grandParent);
    
    AVLNode<Key,Value>* temp = toRotate->getRight();
    n->setParent(toRotate);
    toRotate->setRight(n);
    n->setLeft(temp);

    if(temp != nullptr) temp->setParent(n); //  if the temp pointer is not null then its parent must be the one moving
}

//  rotates the node left
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* toRotate = n->getRight();
    AVLNode<Key,Value>* grandParent = n->getParent();
    if(grandParent != nullptr){
        if(grandParent->getLeft() == n) grandParent->setLeft(toRotate);
        else grandParent->setRight(toRotate);
    }
    else{
        this->root_ = toRotate; // if the grandparent of the parent doesn't exist then root must be parent
    }
    //  swapping pointers
    toRotate->setParent(grandParent);
    
    AVLNode<Key,Value>* temp = toRotate->getLeft();
    n->setParent(toRotate);
    toRotate->setLeft(n);
    n->setRight(temp);

    if(temp != nullptr) temp->setParent(n); //  if the temp pointer is not null then its parent must be the one moving
}

//  changes the balance based on a zig zig
template<class Key, class Value>
void AVLTree<Key, Value>::fixZigZig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p){
    g->setBalance(0);
    p->setBalance(0);
}
//  changes the balance based on if the parent was left of the grandparent
template<class Key, class Value>
void AVLTree<Key, Value>::fixBalance(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* c, bool isRight){
    int change = -1;
    if(isRight) change = 1;
    if(c->getBalance() == char(change)){
        g->setBalance(-change);
        fixZigZig(p, c);
    }
    else if(c->getBalance() == char(-change)){
        p->setBalance(change);
        fixZigZig(g,c);
    }
    else{
        fixZigZig(g,p);
        c->setBalance(0);
    }
}

// fixes the balance after removal, uses a change variable to mirror diff +1 or -1
template<class Key, class Value>
void AVLTree<Key, Value>::removalBalance(AVLNode<Key, Value>* n1, AVLNode<Key, Value>*n2, AVLNode<Key, Value>*n3, bool isRight){
    char change = 1;
    if(isRight) change = -1;
    char n3Balance = n3->getBalance();
    if(n3Balance == char(change)){
        n1->setBalance(0);
        n2->setBalance(-change);
        n3->setBalance(0);
    }
    else if(n3Balance == char(-change)){
        n1->setBalance(change);
        n2->setBalance(0);
        n3->setBalance(0);
    }
    else{
        n1->setBalance(0);
        n2->setBalance(0);
        n3->setBalance(0);
    }
}

#endif
