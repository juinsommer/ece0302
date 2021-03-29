#include "sorted_list.h"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> & x)
{
  plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L>& SortedList<T, L>::operator=(const SortedList<T, L>& x)
{
  plist = x.plist;
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty()
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength()
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T& item)
{

  int position = std::fabs(getPosition(item));
  plist.insert(position, item);
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("DNE");

  int position = getPosition(item);

  if(position > 0)
    plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
   if(isEmpty() || position < 0 || position >= getLength()) throw std::range_error("DNE");
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position)
{
  if(isEmpty() || position < 0 || position >= getLength()) throw std::range_error("DNE");
  return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T& newValue)
{
  int position = 0; 
  int length = plist.getLength();

  while((position < length) && (newValue >= plist.getEntry(position)))
    position++;

  if((position >= length) || (newValue != plist.getEntry(position)))
    position = -position;

  return position;
}
