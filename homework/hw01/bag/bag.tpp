#include "bag.hpp"    
#include <iostream>

template <typename T> Bag<T>::Bag() {}

template <typename T> Bag<T>::~Bag() {}

template <typename T> std::size_t Bag<T>::getCurrentSize() const { return items.size(); }

template <typename T> bool Bag<T>::isEmpty() const { 
    if(items.size() == 0) 
        return true;
    else  
        return false;
}

template <typename T> bool Bag<T>::add(const T& entry) {
    int size1 = items.size();
    items.push_back(entry);
    int size2 = items.size();
    if(size1 < size2)
        return true;
    else
        return false; 
    }

template <typename T> bool Bag<T>::remove(const T& entry) { 
    int size1 = items.size();
    items.pop_back();
    int size2 = items.size();

    if(size1 > size2)
        return true;
    else
        return false;
}

template <typename T> void Bag<T>::clear() { items.clear();}

template <typename T> std::size_t Bag<T>::getFrequencyOf(const T& entry) const {
    int count = 0;
    for(int i = 0; i < items.size(); i++) {
        if(items[i] == entry)
            ++count;
    }
    return count;
 }

template <typename T> bool Bag<T>::contains(const T& entry) const {
    
    if(items.size() != 0)
        return true;
    else
        return false;
}

