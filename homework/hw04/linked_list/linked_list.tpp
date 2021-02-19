#include "linked_list.hpp"

//default constructor initializes the headPtr to be null and numItems 0
template <typename T>
LinkedList<T>::LinkedList() : headPtr(nullptr), numItems(0) {}

//destructor to clear all nodes from list
template <typename T>
LinkedList<T>::~LinkedList() { clear(); }

//copy constructor to perform deep copy of a LinkedList object
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  numItems = x.numItems;
  Node<T>* originListPtr = x.headPtr;

  if(originListPtr == nullptr) //if original is empty
    headPtr = nullptr; 
  
  else {
    headPtr = new Node<T>(); 
    headPtr->setItem(originListPtr->getItem()); //copy first node

    Node<T>* newListPtr = headPtr; //pointer to last node

    originListPtr = originListPtr->getNext(); //advance list

    while(originListPtr != nullptr) { //copy the rest of list
    
      T nextItem = originListPtr->getItem(); //get original item 
      Node<T>* newNode = new Node<T>(nextItem);
      newListPtr->setNext(newNode); //link to end of new list
      newListPtr = newListPtr->getNext(); //advance to last

      originListPtr = originListPtr->getNext(); //advance list
    }
    newListPtr->setNext(nullptr); //flag end
  }
}

//member function to perform a swap of the lists, accepting two LinkedList objects
template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  std::swap(x.numItems, y.numItems); //swap the number of items
  std::swap(x.headPtr, y.headPtr); //swap their head pointers
}

//copy assignmment operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  if(this != &x) {
    numItems = x.numItems;
    Node<T>* originListPtr = x.headPtr;

    if(originListPtr == nullptr)
      headPtr = nullptr;
    
    else {
      headPtr = new Node<T>();
      headPtr->setItem(originListPtr->getItem());

      Node<T>* newListPtr = headPtr;

      originListPtr = originListPtr->getNext();
      while(originListPtr != nullptr) {
        
        T nextItem = originListPtr->getItem();
        Node<T>* newNode = new Node<T>(nextItem);
        newListPtr->setNext(newNode);
        newListPtr = newListPtr->getNext();
        originListPtr = originListPtr->getNext();
      }
      newListPtr->setNext(nullptr);
    }
  }

  return *this;
}
//returns whether the bag contains any items 
template <typename T>
bool LinkedList<T>::isEmpty() const { return (numItems == 0); }

//returns number of items in the list
template <typename T>
std::size_t LinkedList<T>::getLength() const { return numItems;}

//performs an insertion of an item anywhere on the list
template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  Node<T>* newNode = new Node<T>();
  newNode->setItem(item);
  Node<T>* current = headPtr;  //current to track list traversal

  if(position < 1 || position - 1 > numItems) //input validation
    return false;
    
    if(position - 1 == 0) { //if inserting into first position
        newNode->setNext(headPtr);
        headPtr = newNode; //inserted node becomes head pointer
        ++numItems;
        return true;
    }
    
    int counter = 0;
    while( ++counter < position - 1) //traverse the list until i - 1
      current = current->getNext(); 
        
    newNode->setNext(current->getNext()); //set inserted node to be ith node
    current->setNext(newNode);
    
    ++numItems;
    return true;
}

//removes an item anywhere on the list
template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  Node<T>* current = headPtr;
  Node<T>* removeNode = nullptr;

  if(position < 1 || position - 1 > numItems)
    return false;

  int counter = 0;
  while(++counter < position  - 1)
    current = current->getNext(); //at last iteration, i - 1 node 

  removeNode = current->getNext(); // ith node

  current->setNext(removeNode->getNext()); //i + 1 node 

  removeNode->setNext(nullptr);
  delete removeNode; //remove the i node
  removeNode = nullptr;

  numItems--;

 return true;
}

//clears all items from a list
template <typename T>
void LinkedList<T>::clear()
{
  while(headPtr != nullptr) { //traverse to end of list
    Node<T>* deleteNode = headPtr;
    headPtr = headPtr->getNext(); //advance list

    deleteNode->setNext(nullptr);
    delete deleteNode; //remove node
  }

  numItems = 0;

}

//returns the value at a give position on the list
template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  Node<T>* current = headPtr; //pointer to track list traversal

  int count = 0;
  while(++count < position) //traverses list to position 
    current = current->getNext();

  return current->getItem(); //gets value at position
}

//changes a value anywhere on the list without adding another item
template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  Node<T>* current = headPtr; //pointer to track list traversal
  
  int count = 0;
  while(++count < position) //traverses list to position 
    current = current->getNext();

  current->setItem(newValue); //sets value at position
  
}
