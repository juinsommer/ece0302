#include "limited_size_bag.hpp"

//ommited most comments considering all functions are exactly the same
//as dynamic size implementation

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() { numItems = 0;}
  

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag(const LimitedSizeBag& x){ 

  memcpy(this, &x, sizeof(LimitedSizeBag)); //copies non pointer member variables
}
    
template<typename T>
LimitedSizeBag<T>::~LimitedSizeBag(){}
  
template<typename T>
LimitedSizeBag<T>& LimitedSizeBag<T>::operator=(LimitedSizeBag<T>& x)
{  
  if(this != &x)
    memcpy(this, &x, sizeof(LimitedSizeBag));

  return *this;
}

template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
   if(numItems >= MAXSIZE) //if bag is full return false
    return false;

  fixedBag[numItems] = item; 
  ++numItems;
  
  return true;
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  if(numItems == 0)
    return false;

  std::size_t idx = 0;
  for(std::size_t i = 0; i < numItems; ++i){
    if(fixedBag[i] == item)
      break;

    ++idx;
  }

  if(idx == numItems) 
    return false;

  --numItems;
  for(std::size_t i = idx; i < numItems; ++i){
    fixedBag[i] = fixedBag[i+1];
  }

  return true;
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  return (numItems == 0);
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return numItems;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  return (getFrequencyOf(item) != 0);
}

template<typename T>
void LimitedSizeBag<T>::clear(){ numItems = 0;}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  int count = 0;
  for(int i = 0; i < numItems; i++) {
    if(fixedBag[i] == item)
      ++count;
  }

  return count;
};
