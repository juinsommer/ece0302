#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

/*TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
} */

TEST_CASE("testing add() function", "[DynamicBag]") {

  DynamicBag<int> db;
  
  REQUIRE(db.getCurrentSize() == 0);
  
  for(int i = 1; i <= 100; i++) {
    REQUIRE(db.add(i) == true);
    REQUIRE(db.getCurrentSize() == i);
  }
}
