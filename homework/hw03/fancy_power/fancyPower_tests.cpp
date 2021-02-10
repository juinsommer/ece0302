#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cmath>

#include "fancyPower.hpp"

// write your test cases here
TEST_CASE("Test case", "fancyPower"){

  for(int i = 1; i < 10; i++) {

    for(int j = 1; j < 10; j++)
      REQUIRE(fancyPower(i, j) == (int)pow(i, j));

  }
}
