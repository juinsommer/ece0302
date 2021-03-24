#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList() : LinkedList<T>()
{}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x) {}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T>& x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty()
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength()
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
  int position = std::fabs(getPosition(item));
  LinkedList<T>::insert(position, item);
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  int position = getPosition(item);

  if(position > 0)
    LinkedList<T>::remove(position);
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  if(isEmpty() || position < 0 || position >= LinkedList<T>::getLength()) throw std::range_error("empty list in remove");
  
  LinkedList<T>::remove(position);
}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position)
{
  if(isEmpty() || position < 0 || position >= LinkedList<T>::getLength()) throw std::range_error("DNE");
  return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& newValue)
{
  int position = 0;
  
  int length = LinkedList<T>::getLength();
  while((position < length) && (newValue >= LinkedList<T>::getEntry(position)))
    position++;

  if((position >= length) || (newValue != LinkedList<T>::getEntry(position)))
    position = -position;

  return position;
}
