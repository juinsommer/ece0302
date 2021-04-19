#include "list.hpp"

template <typename T>
List<T>::List(): data(nullptr), capacity(0), size(0)
{}

template <typename T>
List<T>::~List()
{
  delete [] data;
}

template <typename T>
List<T>::List(const List<T>& x)
{
  capacity = x.capacity;
  size = x.size;
  data = capacity ? new T[capacity] : nullptr;
  std::copy(x.data, x.data + x.capacity, data);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& x)
{
  if(this != &x) //if assignment is not self referencing
  {
    delete [] data;
    
    data = new T[capacity];

    //copy values from input object
    capacity = x.capacity;
    size = x.size;
    data = capacity ? new T[capacity] : nullptr;
    std::copy(x.data, x.data + x.capacity, data);
  }
  return *this;
}

template <typename T>
bool List<T>::isEmpty() const
{
  return (size == 0);
}

template <typename T>
std::size_t List<T>::getLength() const
{
  return size;
}

template <typename T>
bool List<T>::insert(std::size_t position, const T& item)
{
  if(position - 1 > size || position < 1) throw std::range_error("position out of range in list insert");

  if(size == capacity){ // need to realloc
    std::size_t newcapacity = capacity ? 2*capacity: 1;
    T* newdata = new T[newcapacity];
    std::copy(data, data+capacity, newdata);
    delete [] data;
    capacity = newcapacity;
    data = newdata;
  }

  for(long i = size; i > static_cast<long>(position); --i){
    data[i+1] = data[i];
  }
  
  data[position - 1] = item;
  ++size;

  return true;
}

template <typename T>
bool List<T>::remove(std::size_t position)
{
  if(isEmpty()) throw std::range_error("empty list in list remove");
  if(position > size) throw std::range_error("position out of range in remove");
  
  for(long i = position - 1; i < size; ++i){
    data[i] = data[i+1];
  }
  --size;

  return true;
}

template <typename T>
void List<T>::clear()
{
  size = 0;
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
 if(position > size) throw std::range_error("position out of range in list getEntry");

  return data[position - 1];
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  if(position > size) throw std::range_error("position out of range in list setEntry");

  data[position - 1] = newValue;
}
