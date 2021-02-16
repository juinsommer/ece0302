#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE( "Test insert()", "[ArrayList]" ) {

  ArrayList<int> list;

  for(std::size_t i = 1; i < 50; i++) {
   REQUIRE(list.insert(i, i));
   REQUIRE(list.getEntry(i) == i);
  }
  
  REQUIRE(!list.insert(0, 1));
  REQUIRE(!list.isEmpty());

}

TEST_CASE( "Test remove()", "[ArrayList]" ) {

  ArrayList<int> list;

  for(std::size_t i = 1; i <= 50; i++)
   list.insert(i, i);

  for(std::size_t i = 50; i > 0; i--)
    REQUIRE(list.remove(i));

  REQUIRE(list.isEmpty());
  for(std::size_t i = 1; i <= 10; i++)
    list.insert(i, i);

  REQUIRE(!list.remove(12));

}

TEST_CASE( "Test setEntry()", "[ArrayList]" ) {
  ArrayList<int> list;

  for(std::size_t i = 1; i < 50; i++)
    list.insert(i, i);

  for(std::size_t i = 1; i < 50; i++) {
    list.setEntry(i, i + 1);
    REQUIRE(list.getEntry(i) == i + 1);
  }
}

TEST_CASE( "Test copy constructor", "[ArrayList]") {
  ArrayList<int> list;

  for(std::size_t i = 1; i < 100; i++)
    REQUIRE(list.insert(i, i));

  ArrayList<int> list2(list);

  REQUIRE(list2.getLength() == 99);
  
  for(std::size_t i = 1; i < 100; i++)
    REQUIRE(list2.getEntry(i) == i);
}