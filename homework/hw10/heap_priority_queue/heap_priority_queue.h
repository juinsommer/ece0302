
#ifndef _HEAP_PRIORITY_QUEUE_H_
#define _HEAP_PRIORITY_QUEUE_H_

#include "abstract_priority_queue.h"
#include "dynamic_array_list.h"

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
}

template <typename T>
void HeapPriorityQueue<T>::remove()
{
    if(!isEmpty())
        lst.remove(0);

}

template <typename T>
T HeapPriorityQueue<T>::peek()
{
    return lst.getEntry(0);
}


#endif // _HEAP_PRIORITY_QUEUE_H_
