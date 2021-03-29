#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"

TEST_CASE("Testing Sorted List", "[sorted list]") {

  typedef SortedList<int, DynamicArrayList<int> > slst;
  
  slst l;
  for(int i = 0; i < 10; i++)
    l.insert(i);

  for(int i = 0; i < 10; i++)
    REQUIRE(l.getEntry(i) == i);
}
