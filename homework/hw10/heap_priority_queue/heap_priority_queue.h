
#ifndef _HEAP_PRIORITY_QUEUE_H_
#define _HEAP_PRIORITY_QUEUE_H_

#include "abstract_priority_queue.h"
#include "dynamic_array_list.h"
#include <stdexcept>

template <typename T>
class HeapPriorityQueue: public AbstractPriorityQueue<T>
{
public:
    
    // return true if the priority queue is empty
    bool isEmpty();
    
    // insert item into the queue
    void add(const T& item);
    
    // remove highest priority item from the queue
    void remove();
    
    // get the item with the highest priority from the queue
    T peek();
    
private:
    
    DynamicArrayList<T> lst;
};

template <typename T>
bool HeapPriorityQueue<T>::isEmpty()
{
   return lst.isEmpty();
}

template <typename T>
void HeapPriorityQueue<T>::add(const T& item)
{   
    if(isEmpty())
        lst.insert(0, item);

    else {
        lst.insert(lst.getLength(), item);
        int listSize = lst.getLength() - 1;
        bool inPlace = false;

        while((listSize > 0) && !inPlace) {
            int parentIndex = (listSize) / 2;

            if(lst.getEntry(listSize) < lst.getEntry(parentIndex))
                inPlace = true;

            else {
                T swapItem1 = lst.getEntry(parentIndex);
                T swapItem2 = lst.getEntry(listSize);

                lst.setEntry(listSize, swapItem1);
                lst.setEntry(parentIndex, swapItem2);
                listSize = parentIndex;
            }
        }
    }  
    for(int i = 0; i < lst.getLength();  i++)
        std::cout << lst.getEntry(i) << std::endl;

    std::cout << std::endl;
}

template <typename T>
void HeapPriorityQueue<T>::remove()
{
    int root = 0;
    if(isEmpty()) throw std::range_error("empty heap");

    if(lst.getLength() == 1)
        lst.remove(0);
    
    else {
        lst.remove(0);
        T last = lst.getEntry(lst.getLength() - 1);
        lst.remove(lst.getLength() - 1);
        lst.insert(0, last);

        int largest = 0, 
        leftChild = 2 * root + 1, 
        rightChild = 2 * root + 2;

        while(leftChild < lst.getLength()) {
            
            leftChild = 2 * root + 1;
            rightChild = 2 * root + 2;

            if(leftChild < lst.getLength() && lst.getEntry(leftChild) > lst.getEntry(root))
                largest = leftChild;
            
            if(rightChild < lst.getLength() && lst.getEntry(rightChild) > lst.getEntry(largest))
                largest = rightChild;

            if(largest != 0) {
                T largestItem = lst.getEntry(largest);
                T rootItem = lst.getEntry(root);
                lst.setEntry(root, largestItem);
                lst.setEntry(largest, rootItem);
                root = largest;
            }
        }
    }
}

template <typename T>
T HeapPriorityQueue<T>::peek()
{
    return lst.getEntry(0);
}


#endif // _HEAP_PRIORITY_QUEUE_H_

