#ifndef _LIST_HPP_
#define _LIST_HPP_

#include "abstract_list.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

template <typename T>
class List
{
public:

  // default constructor
  List();
  
  // copy constructor
  List(const List& x);
    
  // destructor
  ~List();
  
  // copy assignment
  List& operator=(List x);

  void swap(List& x, List& y);
  
  // determine if a list is empty
  bool isEmpty();

  // return current lenght of the list
  std::size_t getLength();

  // insert item at position in the list using 0-based indexing
  bool insert(std::size_t position, const T& item);

  // remove item at position in the list using 0-based indexing
  bool remove(std::size_t position);

  // remove all items from the list
  void clear();

  // get a copy of the item at position using 0-based indexing
  T getEntry(std::size_t position);

  // set the value of the item at position using 0-based indexing
  void setEntry(std::size_t position, const T& newValue);

private:

  T * data;
  std::size_t capacity;
  std::size_t size;
  
};

#include "list.tpp"

#endif
