#include "deque.hpp"
#include <stdexcept>

template<typename T>
Deque<T>::Deque() : LinkedList<T>() {}

template<typename T>
Deque<T>::~Deque() {}

template<typename T>
Deque<T>::Deque(const Deque& x) :LinkedList<T>(x) {}

template<typename T>
Deque<T>& Deque<T>:: operator=(const Deque &x) { if(this != &x) LinkedList<T>::operator=(x); return *this;}

template<typename T>
bool Deque<T>::isEmpty() const noexcept { return (LinkedList<T>::getLength() == 0); }

template<typename T>
void Deque<T>::pushFront(const T& item) { LinkedList<T>::insert(0, item); }

template<typename T>
void Deque<T>::popFront() { 
    if(isEmpty()) throw std::runtime_error("deque is empty"); 
    LinkedList<T>::remove(0); 
}

template<typename T>
T Deque<T>::front() const { 
    if(isEmpty()) throw std::runtime_error("deque is empty");
    return LinkedList<T>::getEntry(0); 
}

template<typename T>
void Deque<T>::pushBack(const T& item) { LinkedList<T>::insert(LinkedList<T>::getLength(), item); }

template<typename T>
void Deque<T>::popBack() {
    if(isEmpty()) throw std::runtime_error("deque is empty");
    LinkedList<T>::remove(LinkedList<T>::getLength() - 1);
}

template<typename T>
T Deque<T>::back() const { 
    if(isEmpty()) throw std::runtime_error("deque is empty");
    return LinkedList<T>::getEntry(LinkedList<T>::getLength() - 1); 
}
 
