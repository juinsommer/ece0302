#include "dynamic_bag.hpp"

//default constructor
template<typename T>
DynamicBag<T>::DynamicBag() { bagPtr = new T[maxOut]; }

//copy constructor 
template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag& x){ 
// copy object variables into calling object
  maxOut = x.maxOut;
  numItems = x.numItems;

  bagPtr = new T[maxOut];
  for(int i = 0; i < numItems; i++) 
    bagPtr[i] = x.bagPtr[i];
  
 }
//destructor 
template<typename T>
DynamicBag<T>::~DynamicBag(){ delete [] bagPtr; }

//copy assignment operator
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T>& x)
{  
  if(this != &x) //if assignment is not self referencing
  {
    delete [] bagPtr;
    
    bagPtr = new T[maxOut];

    //copy values from input object
    maxOut = x.maxOut;
    numItems = x.numItems;
    for(int i = 0; i < numItems; i++)
      bagPtr[i] = x.bagPtr[i];

    
  }
  return *this; //return calling object with this ptr
}

//adds an item to the bag, dynamically allocating memory for the item
template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  bool notFull = (numItems < maxOut); //to indicate whether the bag is full or not
  if(!notFull) //if it is full then 
  {
    T* oldBag = bagPtr; //declare ptr to generic type to copy original ptr
    bagPtr = new T[2 * maxOut]; //dynamically allocate more memory to a new array

    for(int i = 0; i < maxOut; i++) //copy items from old array into new
      bagPtr[i] = oldBag[i];

    delete [] oldBag; //free memory from copy ptr
    maxOut = 2 * maxOut; //max array size is now doubled
  }

  bagPtr[numItems] = item; //last element of array now stores argument passed into function, "item"
  numItems++; //increment number of items in bag

  return true;

}

//removes an item from the bag
template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
 if(numItems == 0) //if there is nothing to remove
    return false;

  std::size_t idx = 0;
  //iterates over arrray to find element of item
  for(std::size_t i = 0; i < numItems; ++i){
    if(bagPtr[i] == item) 
      break;
    ++idx;
  }

  if(idx == numItems) //if item was not found
    return false;

  --numItems;
  //avoids gap in the array while removing item
  for(std::size_t i = idx; i < numItems; ++i){
    bagPtr[i] = bagPtr[i+1];
  }

  return true;
}
//returns true if bag is empty, false otherwise
template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  return (numItems == 0);
}

//returns size of bag as integer
template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return numItems;
}

//returns true if item occurs in the bag, false otherwise
template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  return (getFrequencyOf(item) != 0);
}

//empties the bag by setting max size of array to 0
template<typename T>
void DynamicBag<T>::clear(){ maxOut = 0; }

//returns the frequency an item appears in the bag as an integer
template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t freq = 0;

  //if value at element i matches item, freq is incremented
  for(std::size_t i = 0; i < numItems; ++i){
    if(bagPtr[i] == item) 
      ++freq;
  }
  
  return freq;
};
