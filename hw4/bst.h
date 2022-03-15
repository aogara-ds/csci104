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
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);


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
    // Initialize it pointer with value
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // Initialize it pointer as null
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
    // TODO
    // Supposed to check whether the values of this pointer and rhs pointer are equal
    // Might be problems with const-ness, check your methods
    std::cout << "operator ==" << std::endl;
    return this->current_ == rhs.current_;
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
    // TODO
    std::cout << "operator !=" << std::endl;
    return this->current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    std::cout << "operator++" << std::endl;

    // Increments the iterator
    this->current_ = BinarySearchTree<Key, Value>::successor(this->current_);

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
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
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
    std::cout << "begin()" << std::endl;
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
    std::cout << "end()" << std::endl;
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
    std::cout << "insert()" << std::endl;
    // TODO
    const Key key_ = keyValuePair.first;
    const Value value_ = keyValuePair.second;

    std::cout << "key_ = " << key_ << std::endl;
    std::cout << "value_ = " << value_ << std::endl;

    Node<Key, Value>* comp_ = root_;
    bool inserted = false;
    
    if (empty()) {
        std::cout << "empty tree, inserting item at root" << std::endl;
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        inserted = true;
    }

    while (inserted == false)
    {
        if (key_ == comp_->getKey()) {
            std::cout << "same key, overwriting value" << std::endl;
            comp_->setValue(keyValuePair.second);
            inserted = true;
        }

        else if (key_ < comp_->getKey()) {
            if (comp_->getLeft() == NULL) {
                std::cout << "setting left" << std::endl;
                // Am i constructing this boonk???
                comp_->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, comp_));
                inserted = true;
            }

            else {
                std::cout << "walking left" << std::endl;
                comp_ = comp_->getLeft();
            }
        }

        else if (key_ > comp_->getKey()) {
            if (comp_->getRight() == NULL) {
                std::cout << "setting right" << std::endl;
                comp_->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, comp_));
                inserted = true;
            }

            else {
                std::cout << "walking right" << std::endl;
                comp_ = comp_->getRight();
            }
        }

        else {
            std::cout << "you'll never see meeee" << std::endl;
        }
    }
}



/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    std::cout << "remove()" << key << std::endl;

    // Find node to remove
    Node<Key, Value>* rnode = internalFind(key);

    // Non-existent key cannot be removed
    if (rnode == NULL) {
        std::cout << "cannot remove nonexistent node!" << std::endl;
        return;
    }

    // Initialize n_children, parent, and left_child
    int n_children = (rnode->getLeft() != NULL) + (rnode->getRight() != NULL);
    Node<Key, Value>* parent = rnode->getParent();
    bool left_child = false;
    bool removing_root = false;
    if (parent != NULL) left_child = (parent->getLeft() == rnode);
    if (rnode == root_) removing_root = true;

    // Case 1: Two Children
    if (n_children == 2) {
        std::cout << "two children" << std::endl;
        std::cout << "swap with predecessor" << std::endl;

        // this->print();

        // Fetch the successor node
        Node<Key, Value>* rswap = predecessor(rnode);
        Node<Key, Value>* rswap_parent = rswap->getParent();
        Node<Key, Value>* rswap_lc = rswap->getLeft();
        Node<Key, Value>* rswap_rc = rswap->getRight();

        // Parent
        if (removing_root) {
            this->root_ = rswap;
            rswap->setParent(NULL);
            std::cout << "new root is " << this->root_->getKey() << std::endl;
        }
        else {
            std::cout << "parent points to predecessor" << std::endl; 
            if (left_child) parent->setLeft(rswap);
            else parent->setRight(rswap);
        }

        // Children
        if (rnode->getLeft() != rswap) {
            std::cout << rnode->getLeft()->getKey() << "'s parent is now " << rswap->getKey() << std::endl;
            rnode->getLeft()->setParent(rswap);
        }
        if (rnode->getRight() != rswap) {
            std::cout << rnode->getRight()->getKey() << "'s parent is now " << rswap->getKey() << std::endl;
            rnode->getRight()->setParent(rswap);
        }

        // Replacement Node
        rswap->setParent(parent);
        if (rnode->getRight() != rswap) rswap->setRight(rnode->getRight());
        else rswap->setRight(rnode);
        if (rnode->getLeft() != rswap) rswap->setLeft(rnode->getLeft());
        else rswap->setLeft(rnode);

        std::cout << rswap->getKey() << "'s Left is now " << rswap->getLeft()->getKey() << std::endl;
        std::cout << rswap->getKey() << "'s Right is now " << rswap->getRight()->getKey() << std::endl;


        // Removal Node
        if (rswap_parent != rnode) rnode->setParent(rswap_parent);
        else rnode->setParent(rswap);
        rnode->setLeft(rswap_lc);
        rnode->setRight(rswap_rc);

        // Reset params
        n_children = (rnode->getLeft() != NULL) + (rnode->getRight() != NULL);
        parent = rnode->getParent();
        std::cout << "rnode's parent is now " << parent->getKey() << std::endl;
        left_child = false;
        removing_root = false;
        if (parent != NULL) left_child = (parent->getLeft() == rnode);
        if (rnode == root_) removing_root = true;

        std::cout << "left_child bool is " << left_child << std::endl;

        // this->print();
    }

    // Case 2: Zero Children
    if (n_children == 0) {
        std::cout << "zero children" << std::endl;
        std::cout << "delete node" << std::endl;

        delete rnode;
        if (removing_root) this->root_ = nullptr;

        if (parent != NULL) {
            std::cout << "reset parent" << std::endl;
            if (left_child) parent->setLeft(NULL);
            else parent->setRight(NULL);
            std::cout << "reset parent success" << std::endl;
        }

        else std::cout << "null parent" << std::endl;

    }

    // Case 3: One Child
    if (n_children == 1) {
        std::cout << "one child" << std::endl;

        // Store pointer to child
        Node<Key, Value>* rchild;
        if (rnode->getLeft() != NULL) rchild = rnode->getLeft();
        else if (rnode->getRight() != NULL) rchild = rnode->getRight();
        else std::cout << "ERROR in one-child removal" << std::endl;

        // Delete Node
        std::cout << "delete node" << std::endl;
        delete rnode;

        // Promote Child
        if (removing_root) {
            this->root_ = rchild;
            rchild->setParent(NULL);
        }
        else {
            std::cout << "promote child" << std::endl;
            rchild->setParent(parent);
            if (left_child) parent->setLeft(rchild);
            else parent->setRight(rchild);
        }
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    std::cout << "predecessor()" << std::endl;
    Node<Key,Value>* pred;

    // Rightmost child of right subtree
    if (current->getLeft() != NULL) {
        pred = current->getLeft();

        bool has_right = (pred->getRight() != NULL);
        
        while (has_right) {
            pred = pred->getRight();
            has_right = (pred->getRight() != NULL);
        }
    }

    // First parent of a right child ancestor
    else {
        std::cout << "else" << std::endl;
        Node<Key, Value>* child = current;
        Node<Key, Value>* parent = current->getParent();

        bool pred_found = false;

        if (parent == NULL) {
            pred_found = true;
            pred = NULL;
        }

        while (pred_found == false) {
            std::cout << "while" << std::endl;

            if (parent->getRight() == child) {
                std::cout << "if" << std::endl;

                pred = parent;
                pred_found = true;
            }

            else if (parent->getParent() == NULL) {
                std::cout << "else if" << std::endl;

                std::cout << "no predecessor" << std::endl;
                return NULL;
            }

            else {
                std::cout << "else" << std::endl;

                child = parent;
                parent = parent->getParent();
            }
        }
    }

    if (pred == NULL) std::cout << "null predecessor" << std::endl;
    else std::cout << "pred of " << current->getKey() << " is " << pred->getKey() << std::endl;

    return pred;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    std::cout << "successor()" << std::endl;

    Node<Key,Value>* successor;

    // Leftmost child of right subtree
    if (current->getRight() != NULL) {
        successor = current->getRight();

        bool has_left = (successor->getLeft() != NULL);
        
        while (has_left) {
            successor = successor->getLeft();
            has_left = (successor->getLeft() != NULL);
        }
    }

    // First parent of a left child ancestor
    else {
        std::cout << "else" << std::endl;
        Node<Key, Value>* child = current;
        Node<Key, Value>* parent = current->getParent();

        bool successor_found = false;

        if (parent == NULL) {
            successor_found = true;
            successor = NULL;
        }

        while (successor_found == false) {
            std::cout << "while" << std::endl;

            if (parent->getLeft() == child) {
                std::cout << "if" << std::endl;

                successor = parent;
                successor_found = true;
            }

            else if (parent->getParent() == NULL) {
                std::cout << "else if" << std::endl;

                std::cout << "no successor" << std::endl;
                return NULL;
            }

            else {
                std::cout << "else" << std::endl;

                child = parent;
                parent = parent->getParent();
            }
        }
    }

    if (successor == NULL) std::cout << "null successor" << std::endl;
    else std::cout << "successor of " << current->getKey() << " is " << successor->getKey() << std::endl;

    return successor;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    std::cout << "clear()" << std::endl;

    // Find first node
    Node<Key, Value>* curr = this->root_; 
    if (curr == NULL) return;
    while (curr->getLeft() != NULL) curr = curr->getLeft();

    // Find successor
    Node<Key, Value>* snode = successor(curr); 

    // Delete node, move to successor, repeat
    while (snode != NULL) {
        delete curr;
        curr = snode;
        snode = successor(curr); 
    }
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    std::cout << "getSmallestNode()" << std::endl;

    if (empty()) {
        throw std::domain_error("tree is empty, cannot return smallest node");
        return NULL;
    }

    if (root_->getLeft() == NULL) {
        std::cout << "smallest is ROOT" << std::endl;
        return root_;
    }

    Node<Key, Value>* curr = root_;
    bool no_child = false;

    while (no_child == false)
    {
        if (curr->getLeft() == NULL) {
            std::cout << "return smallest" << std::endl;
            no_child = true;
        }

        else {
            std::cout << "walk left" << std::endl;
            curr = curr->getLeft();
        }
    }

    return curr;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    std::cout << "internalFind() " << key << std::endl;
    
    // Begin with root_
    Node<Key, Value>* comp_ = this->root_;

    // Loop down the sorted tree
    while (comp_ != NULL) {
        // std::cout << "while" << std::endl;
        // std::cout << "comp_ = " << comp_->getKey() << std::endl;
        if (comp_->getKey() == key) return comp_;
        if (key < comp_->getKey()) {
            // std::cout << "walk left" << std::endl;
            comp_ = comp_->getLeft();
            // std::cout << "new comp " << comp_->getKey() << std::endl;
        }
        else {
            // std::cout << "walk right" << std::endl;
            comp_ = comp_->getRight();
        }
    }

    // If you reach a NULL node
    std::cout << "no such key!" << std::endl;
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO

    return false;
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
