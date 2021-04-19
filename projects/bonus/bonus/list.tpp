#include "list.hpp"

template <typename T>
List<T>::List(): data(nullptr), capacity(0), size(0)
{}
  
template <typename T>
List<T>::List(const List<T>& x)
{
  capacity = x.capacity;
  size = x.size;
  data = capacity ? new T[capacity] : nullptr;
  std::copy(x.data, x.data + x.capacity, data);
}
    
template <typename T>
List<T>::~List()
{
  delete [] data;
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  swap(*this, x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x, List<T>& y)
{
  std::swap(x.data, y.data);
  std::swap(x.capacity, y.capacity);
  std::swap(x.size, y.size);
}

template <typename T>
bool List<T>::isEmpty()
{
  return (size == 0);
}

template <typename T>
std::size_t List<T>::getLength()
{
  return size;
}

template <typename T>
bool List<T>::insert(std::size_t position, const T& item)
{
  
  if(position -1 > size) throw std::range_error("position out of range in insert");

  if(size == capacity){ // need to realloc
    std::size_t newcapacity = capacity ? 2*capacity: 1;
    T* newdata = new T[newcapacity];
    std::copy(data, data+capacity, newdata);
    delete [] data;
    capacity = newcapacity;
    data = newdata;
  }

  for(long i = size; i > static_cast<long>(position - 1); --i){
    data[i+1] = data[i];
   
  }

  data[position - 1] = item;
  ++size;

  return true;
}

template <typename T>
bool List<T>::remove(std::size_t position)
{

 if(size == 0 || position < 1 || position -1 > size)
    return false;

  --size;

  T* oldData = data; //copy list ptr
  data = new T[capacity];

//copy all elements of array except item to be removed 
  for(std::size_t i = 0; i < position - 1; i++) 
    data[i] = oldData[i];

  for(std::size_t i = position - 1; i < getLength(); i++) 
    data[i] = oldData[i + 1];
  
  delete [] oldData;

  return true;
}

template <typename T>
void List<T>::clear()
{
  size = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position)
{
  if(position > size) throw std::range_error("position out of range in getEntry");

  return data[position - 1];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  if(position > size) throw std::range_error("position out of range in setEntry");

  data[position - 1] = newValue;
}
