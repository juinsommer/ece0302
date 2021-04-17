#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
  State<T> root = queue[0]; //store root
  if(empty()) throw std::range_error("Heap is empty. Cannot remove state.\n");

  if(queue.size() == 1) //if only one state in heap
    queue.pop_back(); //pop the state off the heap

  else { //if there is more than one state in heap
    std::vector<State<T>> copyHeap;
    //maintain heap shape
    copyHeap.push_back(queue[queue.size() - 1]);
    for(std::size_t i = 0; i < queue.size() - 2; i++)
      copyHeap.push_back(queue[i + 1]);

    queue = copyHeap;
    int smallest = 0, 
        leftChild = 2 * smallest + 1, 
        rightChild = 2 * smallest + 2;

    while(root.getFCost() > queue[smallest].getFCost()) {
      root = queue[smallest];
      leftChild = 2 * smallest + 1;
      rightChild = 2 * smallest + 2;

      if(leftChild < queue.size() && queue[leftChild].getFCost() < queue[smallest].getFCost())
        smallest = leftChild;
      
      if(rightChild < queue.size() && queue[rightChild].getFCost() < queue[smallest].getFCost())
        smallest = rightChild;

      if(smallest != 0)
        std::swap(root, queue[smallest]);
    }
  }
    return root;
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  State<T> state(p, cost, heur);
  if(empty()) 
    queue.push_back(state);

  else {
    queue.push_back(state);
    int size = queue.size() - 1;
    int parent = (size - 1) / 2;

    while(size != 0 && queue[parent].getFCost() > queue[size].getFCost()) {
      std::swap(queue[size], queue[parent]);
      size = parent;
    }
  }
  
}

template <typename T>
bool frontier_queue<T>::empty() {
  return queue.empty() ? true : false;
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {
  
  for(int i = 0; i < queue.size(); i++) {
    if(queue[i].getValue() == p)
      return true;
  }
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {

  for(std::size_t i = 0; i < queue.size(); i++) {
    if(queue[i].getPathCost() > cost)
      queue[i].updatePathCost(cost);
  }
}


