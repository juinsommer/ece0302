#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"
#include "priority_queue.h"

TEST_CASE("Testing Priority Queue", "[priority queue]") {

  typedef SortedList<int, DynamicArrayList<int> > SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;
  
  for(int i = 1; i <= 100; i++)
    pq.add(i);

  REQUIRE(pq.peek() == 100);

  for(int i = 1; i <= 100; i++) {
    REQUIRE(pq.peek() == 101 - i);
    pq.remove();
  }

  REQUIRE(pq.isEmpty());


  pq.add(5);
  pq.add(2);
  pq.add(3);
  pq.add(1);
  pq.add(4);

  for(int i = 5; i > 1; i--) {
    REQUIRE(pq.peek() == i);
    pq.remove();
    REQUIRE(pq.peek() == i - 1);
  }
}
