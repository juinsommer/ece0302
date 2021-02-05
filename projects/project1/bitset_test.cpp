#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"

TEST_CASE( "Test size function", "[bitset]") {

    Bitset b(64);
    REQUIRE(b.size() == 64);
}

TEST_CASE( "Test bitset construction", "[bitset]" ) {

    Bitset b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good() == true);
    REQUIRE(b.asString() == "00000000");
}

TEST_CASE( "Test construction of bitset size N", "[bitset]") {

    Bitset b(16);
    REQUIRE(b.size() == 16);
    REQUIRE(b.good() == true);
}

TEST_CASE( "Test good function", "[bitset]") {

    Bitset b(32);
    REQUIRE(b.size() == 32);
    b.set(35); //attemps to set an element outside of array to 1
    REQUIRE(b.good() == false); //proves bitset is now invalid

}
TEST_CASE( "Test asstring function", "[bitset]") {

    Bitset b;
    b.set(1);
    b.set(3);
    REQUIRE(b.asString() == "10100000");
}

TEST_CASE( "Test construction of bitset with string", "[bitset]") {

    Bitset b("10000000");
    REQUIRE(b.asString() == "10000000");
    REQUIRE(b.good() == true);

    Bitset b2("31002001"); //input invalid bitset
    REQUIRE(b2.good() == false); //proves function indicates invalid bitset
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

TEST_CASE( "Test test function", "[bitset]" ) {

    Bitset b; 
    b.set(1);
    REQUIRE(b.good() == true); 
}

