#include "bag.hpp"    
#include <iostream>  
#include <vector>

template <typename T> Bag<T>::Bag() {}

template <typename T> Bag<T>::~Bag() {}

template <typename T> std::size_t Bag<T>::getCurrentSize() const { 
    int numItems = 0;
    for(int i = 0; i < 10; i++) 
        numItems += item[i];
        
    return numItems;
}

template <typename T> bool Bag<T>::isEmpty() const { 
    int things = 0;
    for(int i = 0; i < 10; i++) 
        things += item[i];
        
    if(things == 0)
            return true; 
        else 
            return false; 
    }

template <typename T> bool Bag<T>::add(const T& entry) {
    
    return false; 
    }

template <typename T> bool Bag<T>::remove(const T& entry) { return false; }

template <typename T> void Bag<T>::clear() {}

template <typename T> std::size_t Bag<T>::getFrequencyOf(const T& entry) const { return 0; }

template <typename T> bool Bag<T>::contains(const T& entry) const { return false; }

