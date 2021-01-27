#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "bag.hpp"

// force template expansion
template class Bag<int>;

TEST_CASE("Empty Test", "[isEmpty()]"){

  Bag<bool>b;
  REQUIRE(b.isEmpty() == false);
}

TEST_CASE("CurrentSize", "[getCurrentSize()]"){

  Bag<int>b;
  REQUIRE(b.getCurrentSize()== 1);
}

/*TEST_CASE("Add an item", "[add()]"){

  Bag<bool>b;

  REQUIRE(b.add(const T& entry) == 1 );
}*/