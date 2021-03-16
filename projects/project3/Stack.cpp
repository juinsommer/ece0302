//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

//default constructor initializing headPtr to nullptr
template<class ItemType>
Stack<ItemType>::Stack() : headPtr(nullptr) { currentSize = 0; }  // end default constructor

//empty stack
template<class ItemType>
Stack<ItemType>::~Stack() { clear(); }  // end destructor

//return bool whether stack is empty or not
template<class ItemType>
bool Stack<ItemType>::isEmpty() const { return (headPtr == nullptr); }  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const { return currentSize; }  // end size

//push new node to stack
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	//define node ptr to point to a new node initialized with the item to be added and the headptr
	Node<ItemType> *newNodePtr = new Node<ItemType>(newItem, headPtr); 
	//copy new node address to headptr
	headPtr = newNodePtr;
	newNodePtr = nullptr;
	++currentSize;
	return true;
}  // end push

//returns last item in stack
template<class ItemType>
ItemType Stack<ItemType>::peek() const throw (logic_error)
{ 
		return (isEmpty()? throw logic_error("Stack is empty") : headPtr->getItem());
}  // end peek

//remove item at top of the stack
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	bool result = false;
	//if stack is not empty then remove item
	if(!isEmpty()) {
		Node<ItemType> *deleteNodePtr = headPtr;
		headPtr = headPtr->getNext();

		//delete node from stack
		deleteNodePtr->setNext(nullptr);
		delete deleteNodePtr;
		deleteNodePtr = nullptr;
		--currentSize;
		result = true;
	}
	return result;
}  // end pop

//remove items until empty
template<class ItemType>
void Stack<ItemType>::clear()
{
	while(!isEmpty())
		pop();
	currentSize = 0;
}  // end clear

