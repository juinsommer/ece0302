#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "bag.hpp"
#include <string>

// force template expansion
template class Bag<int>;

TEST_CASE("Empty Test", "[isEmpty()]"){

  Bag<int>b;
  
  REQUIRE(b.isEmpty() == true);

  int count = 0;
  for(int i = 0; i < b.getVector().size(); i++)
    count = b.getVector()[i];

  REQUIRE(count == 0);  

}

TEST_CASE("CurrentSize", "[getCurrentSize()]"){

  Bag<int> b;
  REQUIRE(b.getCurrentSize()== 0);

  b.add(1);
  int count = 0;
  for(int i = 0; i < b.getVector().size(); i++)
   count = b.getVector()[i];

  REQUIRE(count == 1);
}

TEST_CASE("Add an item", "[add()]"){

  Bag<int> b;
  Bag<std::string> a;
  std::string str = " ";

  REQUIRE(b.add(1) == true ); 
  REQUIRE(a.add(str) == true );

}

TEST_CASE("remove an item", "[remove()]"){

  Bag<int> b;
  

  b.add(1);
  REQUIRE(b.getCurrentSize() == 1);
  REQUIRE(b.remove(1) == true);
  REQUIRE(b.isEmpty() == true);

  Bag<std::string> a;
  std::string str = " ";
  a.add(str);
  REQUIRE(a.getCurrentSize() == 1);
  REQUIRE(a.remove(str) == true);
  REQUIRE(a.isEmpty() == true);



}

TEST_CASE("clear items", "[clear()]"){
  Bag<int> b;

  REQUIRE(b.add(1) == true);
  REQUIRE(b.isEmpty() == false);
  b.clear();
  REQUIRE(b.isEmpty() == true);
}

TEST_CASE("frequency of item appearance", "[getFrequency]"){
  Bag<int> b; 
  b.add(1);
  b.add(1);
  REQUIRE(b.getFrequencyOf(1) == 2);

  Bag<std::string> a;
  a.add("1");
  REQUIRE(a.getFrequencyOf("1") == 1);

}

TEST_CASE("contains at least one item", "[contains()]"){
  Bag<int> b;

  b.add(1);
  REQUIRE(b.contains(1) == true);
}