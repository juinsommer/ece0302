#include "binary_search_tree.h"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    clone(rhs.root);
}

// this is an alternative implementation using a stack to simulate the recursion
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::clone(Node<KeyType, ItemType>* rhs)
{
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(const BinarySearchTree<KeyType, ItemType>& rhs)
{
    if (&rhs == this)
        return *this;

    destroy();

    root = 0;
    clone(rhs.root);

    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    Node<KeyType, ItemType>* curr, *curr_parent;
    Node<KeyType, ItemType>* newNodePtr = new Node<KeyType, ItemType>;

    search(key, curr, curr_parent);
    newNodePtr->data = item;
    newNodePtr->key = key;

    if(root == 0)
        root = newNodePtr;

    if (curr != 0) {
        if(key < curr->key) {
            curr->left = newNodePtr;
            return true;
        }
        else if(key > curr->key) {
           curr->right = newNodePtr;
            return true;
        }
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
        return false; // empty tree

    Node<KeyType, ItemType>* curr = root;
    Node<KeyType, ItemType>* curr_parent = nullptr;
    search(key, curr, curr_parent);

    //node is a leaf
    if(curr->left == nullptr && curr->right == nullptr) {
        //if not a root node, then set parent child to null
        if(curr != root) {
            if(curr_parent->left == curr)
                curr_parent->left = nullptr;

            else 
                curr_parent->right = nullptr;
        }
        // case one thing in the tree
        else 
            root = nullptr;

        delete curr;
        return true;
    }
    //node has two children
    if(curr->left && curr->right) {
        Node<KeyType, ItemType>* successor;
        //find inorder successor
        inorder(curr->right, successor, curr_parent);
        //copy its data
        curr->data = successor->data;
        //recursively remove successor
        remove(successor->key);
        return true;
    }
    //node has one child
    else {
        Node<KeyType, ItemType>* child;
        //assign child to left if left child of current not null, otherwise assign right
        child = (curr->left) ? curr->left : curr->right;

        //if not a root node, assign parents to its child
        if(curr != root) {
            if(curr == curr_parent->left)
                curr_parent->left = child;

            else 
                curr_parent->right = child;
        }
        //if root node, set root to child
        else
            root = child;
        
        delete curr;
        return true;
    }

    return false; // default should never get here
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    curr = parent;
    std::stack<Node< KeyType, ItemType>* > s;

    int i = 0;
    while(curr != nullptr || !s.empty()) {
        while(curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();
        in = curr;

        curr = curr->right;
    }
      
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(ItemType arr[], int size) {

    Node<KeyType, ItemType> *curr;
    // TODO: check for duplicate items in the input array

    // use the tree to sort the array items
    for(int i = 0; i < size; i++) {
        insert(arr[i], arr[i]);
    }

    curr = root;
    std::stack<Node< KeyType, ItemType>* > s;

    int i = 0;
    while(curr != nullptr || !s.empty()) {
        while(curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();
        arr[i++] = curr->data;

        curr = curr->right;
    } 
}  
