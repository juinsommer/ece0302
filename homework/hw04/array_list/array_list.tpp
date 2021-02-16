#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList() { 
  numItems = 0;
  list = new T[maxSize];
  }

template <typename T>
ArrayList<T>::~ArrayList() { delete [] list; }

//copy constructor
template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs){
  
  maxSize = rhs.maxSize;
  numItems = rhs.numItems;
  list = new T[maxSize];
  std::memcpy(this->list, rhs.list, numItems * sizeof(T)); //copy ptr member variable (just to make a little cleaner)
}

//copy assignment operator
template <typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList<T>& rhs){

  if(this != &rhs) { //if not self-referencing copy object
    delete [] list;
    list = new T[maxSize];

    maxSize = rhs.maxSize;
    numItems = rhs.numItems;
    std::memcpy(this->list, rhs.list, numItems * sizeof(T));
  }
  return *this;
}

template <typename T>
bool ArrayList<T>::isEmpty() const{ return (numItems == 0); }

template <typename T>
std::size_t ArrayList<T>::getLength() const{ return numItems; }

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){

  bool notFull = (numItems < maxSize);

  if(position < 1 || position - 1 > numItems)
    return false;

    else if(!notFull) { //if bag is full
      T* oldList = list; //copy list ptr

      list = new T[2 * maxSize]; //dynamically allocate new memory
      for(std::size_t i = position - 1; i < numItems; i++) //avoiding gap in array from adding at specified position
        list[i] = list[i + 1];

      delete [] oldList; 
      maxSize = 2 * maxSize; //change max size of array
      
  }

  list[position - 1] = item; //assign element at position - 1 to be item
  numItems++;
  
  return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){

  if(numItems == 0 || position < 1 || position -1 > numItems)
    return false;

  numItems--;

  for(std::size_t i = position - 1; i < numItems; i++)
    list[i] = list[i + 1];

  return true;
  
}

template <typename T>
void ArrayList<T>::clear() { maxSize = 0;}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const { return list[position - 1]; }

//*************************************************
//what happens if position is out of range of array?
//*************************************************
template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {list[position - 1] = newValue;} 
