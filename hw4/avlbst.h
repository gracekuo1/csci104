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
    int8_t getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;
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
int8_t AVLNode<Key, Value>::getBalance() const
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
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void rotateRight (AVLNode<Key,Value>* node);
    virtual void rotateLeft (AVLNode<Key,Value>* node);
    virtual void insertFix (AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    virtual void removeFix (AVLNode<Key, Value>* n, int diff);


};

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key,Value>* z){
    AVLNode <Key,Value> *y = z->getLeft();
    //AVLNode <Key,Value> *x = y->getLeft();
    AVLNode <Key,Value> *c = y->getRight();
    //if the parent is the root
    if (z == this->root_){
        this->root_ = y;
        y->setParent(nullptr);
        z->setParent(y);
        y->setRight(z);
        z->setLeft(c);
        if (c != nullptr)
            c->setParent(z);
    }
    else {
        AVLNode <Key,Value> *p = z->getParent();
        y->setParent(p);
        y->setRight(z);
        if (p->getRight() == z){
            p->setRight(y);
        }
        else {
             p->setLeft(y);
        }
        z->setParent(y);
        if (c!=nullptr)
            c->setParent(z);
        z->setLeft(c);
    }

}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key,Value>* x){
    AVLNode <Key,Value> *y = x->getRight();
    //AVLNode <Key,Value> *z = y->getRight();
    AVLNode <Key,Value> *b = y->getLeft();

    if (x == this->root_){
        this->root_ = y;
        y->setParent(nullptr);
        x->setParent(y);
        y->setLeft(x);
        x->setRight(b);
        if (b!= nullptr)
            b->setParent(x);
    }
    else{
        AVLNode <Key,Value> *p = x->getParent();
        y->setParent(p);
        y->setLeft(x);
        if (p->getRight() == x){
            p->setRight(y);
        }
        else {
            p->setLeft(y);
        }
        x->setParent(y);
        if (b!=nullptr)
            b->setParent(x);
        x->setRight(b);

    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
    if (p == nullptr || p->getParent() == nullptr)
        return;

    AVLNode<Key, Value>* g = p->getParent();

    if (p == g->getLeft()){
        g->setBalance(g->getBalance() -1);
        if (g->getBalance() == 0)
            return;
        else if (g->getBalance() == -1)
            insertFix(g, p);
        else if (g->getBalance() == -2){
            if (g->getLeft()->getLeft() == n){//do you need to do g.getParent()
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            else {
                rotateLeft(p);
                rotateRight(g);
                if (n->getBalance() == -1){
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 1){
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
    else if (p == g->getRight()){
        g->setBalance(g->getBalance() +1);
        if (g->getBalance() == 0)
            return;
        else if (g->getBalance() == 1)
            insertFix(g, p);
        else if (g->getBalance() == 2){
            if (g->getRight()->getRight() == n){ //same here
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            else {
                rotateRight(p);
                rotateLeft(g);
                if (n->getBalance() == -1){
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if (n->getBalance() == 1){
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
            }
        }
    }

}
/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    AVLNode<Key, Value> *curr =  static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value> *newN = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    bool cont = true;
    if (this->root_ == NULL){
        this->root_ = newN;
    }
    else
    {
        while (cont){
            if (new_item.first < curr->getKey()){
                if (curr->getLeft() == NULL){
                    curr->setLeft(newN);
                    newN->setParent(curr);
                    cont = false;
                    newN->setBalance(0);
                    if (newN->getParent()->getBalance() == -1 ||
                    newN->getParent()->getBalance() == 1 )
                        newN->getParent()->setBalance(0);
                    else if (newN->getParent()->getBalance() == 0){
                        newN->getParent()->setBalance(-1);
                        insertFix(newN->getParent(), newN);
                    }
                }
                else{
                    //curr->setBalance(curr->getBalance()-1); //add f
                    curr = curr->getLeft();
                }
            }
            else if (new_item.first > curr->getKey()){
                if (curr->getRight() == NULL){
                    curr->setRight(newN);
                    newN->setParent(curr);
                    cont = false;
                    newN->setBalance(0);
                    if (newN->getParent()->getBalance() == -1 ||
                    newN->getParent()->getBalance() == -1 )
                        newN->getParent()->setBalance(0);
                    else if (newN->getParent()->getBalance() == 0){
                        newN->getParent()->setBalance(1);
                        insertFix(newN->getParent(), newN);
                    }
                }
                else{
                    //curr->setBalance(curr->getBalance()+1); //add f
                    curr = curr->getRight();
                }

            }
            else {
                curr->setValue(new_item.second);
                delete newN;
                cont = false;
            }
        }
    }
    //this->print();
}


template<class Key, class Value>
void AVLTree<Key, Value>::removeFix (AVLNode<Key, Value>* n, int diff)
{
    if (n==nullptr)
        return;
    
    int ndiff = -1;
    AVLNode<Key, Value> *p = n->getParent();
    if (p!=nullptr){
        if (n == p->getLeft()){
            ndiff = 1;
        }
        
    }
    
    if (diff == -1){
        if (n->getBalance() + diff == -2){
            AVLNode<Key, Value> *c = n->getLeft();
            if (c->getBalance() == -1){
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0){
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
            }
            else if (c->getBalance() == 1){
                AVLNode<Key, Value> *g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if (g->getBalance() == 1){
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == -1){
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }

        }
        else if (n->getBalance() + diff == -1)
            n->setBalance(-1);
        else if (n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    else if (diff == 1){
        if (n->getBalance() + diff == 2){
            AVLNode<Key, Value> *c = n->getRight();
            if (c->getBalance() == 1){
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if (c->getBalance() == 0){
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
            }
            else if (c->getBalance() == -1){
                AVLNode<Key, Value> *g = c->getLeft();
                //std::cout << "before right rotate" << std::endl;
                //this->print();
                rotateRight(c);
                //std::cout << "after right rotate" << std::endl;
                //this->print();
                rotateLeft(n);
                //std::cout << "after left rotate" << std::endl;
                //this->print();
               
                if (g->getBalance() == -1){
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if (g->getBalance() == 1){
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }

        }
        else if (n->getBalance() + diff == 1)
            n->setBalance(1);
        else if (n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
        
    
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value> *curr = static_cast<AVLNode<Key,Value>*>(this->root_);
    AVLNode<Key, Value> *past = nullptr;
    bool left = true;

    if (curr == nullptr)
        return;
    //walk to value
    while (curr->getKey() != key && curr != nullptr){
        if (key < curr->getKey()){
            if (curr->getLeft() == nullptr)
                return;
            past = curr;
            //left = true;
            curr = curr->getLeft();
        }
        else if (key > curr->getKey()){
            if (curr->getRight() == nullptr)
                return;
            past = curr;
            //left = false;
            curr = curr->getRight();
        }
    }
    //std::cout << "value to remove" << curr->getKey() << std::endl;

    
    //there are 2 leaves
    if (curr->getLeft() != nullptr && curr->getRight() != nullptr){
        //std::cout << "swap" << std::endl;
        AVLNode<Key, Value> *pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(curr));
        //switch current node and predecessor
        nodeSwap(curr, pred);
        past = curr->getParent();
    }

    past = curr->getParent();

    //check if it is truely left
    if (curr != nullptr && curr->getParent() != nullptr && 
        curr->getParent()->getLeft() != curr){
        left = false;
    }
    else
        left = true;

    int diff = 0;

    if (left){
        diff = 1;
    }
    else {
        diff = -1;
    }
    //past->setBalance(past->getBalance()+diff); fishy
    
    if ((curr->getLeft() == nullptr) && (curr->getRight() == nullptr)){
        //std::cout << "no leaves" << std::endl;
        if (left){
            if (curr == this->root_)
                this->root_ = nullptr;
            else 
                past->setLeft(nullptr);
            delete curr;
        }
        else {
            if (curr == this->root_)
                this->root_ = nullptr;
            else 
                past->setRight(nullptr);
            delete curr;
        }
    }
    //if one right leaf
    else if (curr->getLeft() == nullptr){
        //std::cout << "one right leaf" << std::endl;
        if (curr == this->root_){
            this->root_ = curr->getRight();
            this->root_->setParent(nullptr);
        }
        else {
            Node<Key, Value> *right_child = curr->getRight();
            if (left)
                past->setLeft(right_child);
            else 
                past->setRight(right_child);
            right_child->setParent(past);
        }
        delete curr;
    }
    //if one left leaf
    else if (curr->getRight() == nullptr){
        //std::cout << "one left leaf" << std::endl;
        if (curr == this->root_){
            this->root_ = curr->getLeft();
            this->root_->setParent(nullptr);
        }
        else {
            Node<Key, Value> *left_child = curr->getLeft();
            if (left)
                past->setLeft(left_child);
            else 
                past->setRight(left_child);
            left_child->setParent(past);
        }
        delete curr;
    }
    //root_ = deleteNode(root_, key);
    //std::cout << "done removing" << std::endl;

    //this->print();
    removeFix(past, diff);
    
    //std::cout << "done remove fix" << std::endl;


    //this->print();
    
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
