#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

TEST_CASE( "Tests", "[deque]" ) {
    Deque<int> d;

    for(std::size_t i = 1; i <= 10; i++)
        d.pushFront(i);
    
    REQUIRE(!d.isEmpty());
    REQUIRE(d.front() == 10);
    REQUIRE(d.back() == 1);

   
    for(std::size_t i = 10; i >= 1; i--) {
        INFO("test popFront() and front()");
        REQUIRE(d.front() == i);
        d.popFront();
    }

    INFO("test pushBack()");
    Deque<int> d2;
    
    for(std::size_t i = 1; i <= 10; i++) {
        d2.pushBack(i);
        REQUIRE(d2.back() == i);
    }

    d2.pushBack(11);
    REQUIRE(d2.back() == 11);
    REQUIRE(d2.front() == 1);

    INFO("test popBack()");
    for(std::size_t i = 11; i >= 1; i--) {
        REQUIRE(d2.back() == i);
        d2.popBack();
    }

    INFO("test exceptions");
    Deque<int> d3;
    CHECK_THROWS_AS(d3.popBack(), std::runtime_error);
    CHECK_THROWS_AS(d3.popFront(), std::runtime_error);
    CHECK_THROWS_AS(d3.front(), std::runtime_error);
    CHECK_THROWS_AS(d3.back(), std::runtime_error);

    INFO("test copy assignment operator and copy constructor");
    Deque<int> d4, d5;
    for(std::size_t i = 1; i <= 1000; i++) {
        d4.pushBack(i);
        REQUIRE(d4.back() == i);
    }
    d5 = d4;
    for(std::size_t i = 1; i <= 1000; i++) {
        REQUIRE(d5.front() == i);
        d5.popFront();
    }
    REQUIRE(d5.isEmpty());

    for(std::size_t i = 1; i <= 10; i++)
        d5.pushBack(i);
    
    Deque<int> d6(d5);
    REQUIRE(d6.back() == 10);
    REQUIRE(d6.front() == 1);
    
}