#include "dynamic_array_list.h"

#include <algorithm>
#include <stdexcept>

#include <iostream>

template <typename T>
DynamicArrayList<T>::DynamicArrayList() : size(0)
{
  data = new T[capacity];
}
  
template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T>& x)
{
  capacity = x.capacity;
  size = x.size;

  data = new T[capacity];
  memcpy(this->data, x.data, size*sizeof(T));
}
    
template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
  std::clog << "DynamicArrayList Destructor called." << std::endl;

  clear();
}

template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> x)
{
  if(this != &x) {
    
    delete [] data;
    capacity = x.capacity;
    size = x.size;

    data = new T[capacity];
    memcpy(this->data, x.data, size*sizeof(T));
  }
  return *this;
}

template <typename T>
void DynamicArrayList<T>::swap(DynamicArrayList<T>& y)
{
  std::swap(this->size, y.size);
  std::swap(this->capacity, y.capacity);
  std::swap(this->data, y.data);
}

template <typename T>
bool DynamicArrayList<T>::isEmpty()
{
  return (size == 0) ? true : false;
}

template <typename T>
std::size_t DynamicArrayList<T>::getLength()
{
  return size;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item)
{
  bool isFull = (size < capacity);
  if(isFull) {

    T* oldData = data;
    data = new T[2 * capacity];

   for(std::size_t i = 0; i < capacity; i++)
    data[i] = oldData[i];

    delete [] oldData;
    capacity = 2 * capacity;
  }

  data[position] = item;
  size++;

}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t position)
{
  if(isEmpty() || position < 0 || position > size)
    throw std::logic_error("cannot remove item. Queue empty or position is out of range");

  --size;
  for(std::size_t i = position; i < size; i++)
    data[i] = data[i + 1];

}

template <typename T>
void DynamicArrayList<T>::clear()
{
  delete [] data;
  capacity = 50;
  size = 0;
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position)
{
  if(isEmpty() || position > size || position < 0)
    throw std::logic_error("entry does not exist or position is out of range");

  return data[position];
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
  if(position > size || position < 0)
    throw std::logic_error("position is out of range");

  data[position] = newValue;
}
