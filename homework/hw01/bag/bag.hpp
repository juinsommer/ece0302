#ifndef STUDENT_BAG_HPP
#define STUDENT_BAG_HPP

#include <cstdlib>
#include <vector>

template<typename T> class Bag{
public:

  Bag();
  
  ~Bag();

  std::size_t getCurrentSize() const;

  bool isEmpty() const;

  bool add(const T& entry);

  bool remove(const T& entry);

  void clear();

  std::size_t getFrequencyOf(const T& entry) const;

  bool contains(const T& entry) const;

  std::vector<T> getVector() const { return items; }

private: 

  std::vector<T> items;

};


#include "bag.tpp"

#endif
