#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE( "Test insert()", "[LinkedList]" ) {

    LinkedList<int> list;

    for(std::size_t i = 1; i <= 25; i++) {
        REQUIRE(list.insert(i, i));
        REQUIRE(list.getEntry(i) == i);
    }

    REQUIRE(list.insert(20, 0));
    REQUIRE(list.getEntry(20) == 0);
    REQUIRE(list.getEntry(19) == 19);
    REQUIRE(list.getEntry(21) == 20);
    REQUIRE(list.getLength() == 26);

    LinkedList<int> list2;

    for(std::size_t i = 1; i <= 25; i++)
        REQUIRE(list2.insert(i, i));

    REQUIRE(list2.insert(1, 0));
    REQUIRE(list2.getEntry(1) == 0);

    REQUIRE(list2.insert(27, 0));
    REQUIRE(list2.getEntry(27) == 0);
    REQUIRE(list2.getEntry(26) == 25);
}

TEST_CASE( "Test remove()", "[LinkedList]" ) {

    LinkedList<int> list;

    for(std::size_t i = 1; i <= 10; i++)
        list.insert(i, i);

    REQUIRE(list.remove(5));
    REQUIRE(list.getEntry(5) == 6);
    REQUIRE(list.getLength() == 9);
}
 TEST_CASE("Test copy constructor", "[LinkedList]") {

     LinkedList<int> list;

    for(std::size_t i = 1; i <= 25; i++)
        REQUIRE(list.insert(i, i));

    LinkedList<int> list2(list);

    for(std::size_t i = 1; i <= 25; i++)
        REQUIRE(list2.getEntry(i) == i); 

 } 

 TEST_CASE("Test copy assignment operator", "[LinkedList]") {

     LinkedList<int> list;

     for(std::size_t i = 1; i <= 100; i++)
        REQUIRE(list.insert(i, i));

    LinkedList<int> list2;

    list2 = list;

    for(std::size_t i = 1; i <= 100; i++)
        REQUIRE(list2.getEntry(i) == i);

 }
 TEST_CASE("Test clear()", "[LinkedList]") {

    LinkedList<int> list;

    for(std::size_t i = 1; i <= 25; i++)
        list.insert(i, i);

    list.clear();
    REQUIRE(list.getLength() == 0);
 }

 TEST_CASE("Test swap()", "[LinkedList]") {

    LinkedList<int> list, list2;
    for(std::size_t i = 1; i <= 10; i++)
        list.insert(i, i);

    for(std::size_t i = 1; i <= 10; i++)
        list2.insert(i, i + 1);

    list.swap(list, list2);
    for(std::size_t i = 1; i <= 10; i++)
        REQUIRE(list.getEntry(i) == i + 1);

 }

 TEST_CASE("Test setEntry()", "[LinkedList]") {

     LinkedList<int> list;
     for(std::size_t i = 1; i <= 10; i++)
        list.insert(i, i);

    list.setEntry(1, 0);

    REQUIRE(list.getEntry(1) == 0);
    REQUIRE(list.getEntry(2) == 2);

    for(std::size_t i = 1; i <= 10; i++)
        list.setEntry(i, 0);

    for(std::size_t i = 1; i <= 10; i++)
        REQUIRE(list.getEntry(i) == 0);
 }

 TEST_CASE("Test getEntry()", "[LinkedList]") {

    LinkedList<int> list;
    for(std::size_t i = 1; i <= 100; i++)
       REQUIRE(list.insert(i, i));

    for(std::size_t i = 1; i <= 100; i++)
        REQUIRE(list.getEntry(i) == i);
    
 }