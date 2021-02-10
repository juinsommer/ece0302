#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() { bagPtr = new T[maxOut]; }
  
template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag& x){}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){ delete [] bagPtr; }

template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T>& x)
{  
  return *this;
}

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

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  return false;
}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  return false;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return numItems;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  return false;
}

template<typename T>
void DynamicBag<T>::clear(){}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  return 0;
};
