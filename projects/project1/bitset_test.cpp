#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"

// THIS IS JUST AN EXAMPLE
// There should be at least one test per Bitset method

TEST_CASE( "Test bitset construction", "[bitset]" ) {

    Bitset b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good() == true);
}

TEST_CASE( "Test construction of bitset size N", "[bitset]") {
    Bitset b(16);
    REQUIRE(b.size() == 16);
}

TEST_CASE( "Test construction of bitset with string", "[bitset]") {
    Bitset b("10000000");
    REQUIRE(b.asString() == "10000000");
    REQUIRE(b.good() == true);
}

TEST_CASE( "test set function", "[bitset]") {
    Bitset b;
    b.set(2);
    REQUIRE(b.good() == true);
    REQUIRE(b.test(2) == true);
}

TEST_CASE( "Test reset function", "[bitset]") {
    Bitset b;
    b.set(1);
    REQUIRE(b.test(1) == true);
    b.reset(1);
    REQUIRE(b.test(1) == false);
    REQUIRE(b.good() == true);
}

TEST_CASE( "Test toggle function", "[bitset]") {
    Bitset b;
    b.toggle(1);
    REQUIRE(b.test(1) == true);
}


