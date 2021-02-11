#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("testing add()", "[DynamicBag]") {

  DynamicBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < 200; ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(b.isEmpty() == false);
  }

}

TEST_CASE("testing copy constructor", "[DynamicBag]") {

  DynamicBag<int> d1;

  for(int i = 0; i < 100; i++)
    d1.add(i);

   DynamicBag<int> d2(d1);
  REQUIRE(d2.getCurrentSize() == 100);
}

TEST_CASE("Test clear()", "[DynamicBag]"){

  DynamicBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
  b.clear();
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < b.getCurrentSize(); ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  b.clear();
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
  
}

TEST_CASE("Test getfrequency()", "[DynamicBag]"){

  {
    DynamicBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(b.getFrequencyOf(0) == 0);
    
    for(int i = 0; i < b.getCurrentSize(); ++i){
      REQUIRE(b.add(i));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }
    
    for(int i = 0; i < b.getCurrentSize(); ++i){
      REQUIRE(b.getFrequencyOf(i) == 1);
    }
  }
  
  {
    DynamicBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    
    for(int i = 0; i < b.getCurrentSize(); ++i){
      REQUIRE(b.add(-1));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }

    std::size_t EXPECTED = b.getCurrentSize();
    REQUIRE(b.getFrequencyOf(-1) == EXPECTED);
    REQUIRE(b.getFrequencyOf(0) == 0);
  }
}

TEST_CASE("Test contains()", "[DynamicBag]"){

  {
    DynamicBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(!b.contains(0));
	
    for(int i = 0; i < 100; ++i){
      REQUIRE(b.add(i));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }
    
    for(int i = 0; i < 100; ++i){
      REQUIRE(b.contains(i));
    }
    REQUIRE(!b.contains(-1));
  }
  
  {
    DynamicBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(!b.contains(0));
    
    for(int i = 0; i < 100; ++i){
      REQUIRE(b.add(-1));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }

    REQUIRE(b.contains(-1));
    REQUIRE(!b.contains(0));
  }
}

TEST_CASE("Test remove()", "[DynamicBag]"){

  DynamicBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < 100; ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  REQUIRE(!b.remove(-1));
  
  for(int i = 0; i < 100; ++i){
    REQUIRE(b.remove(i));
  }
  REQUIRE(!b.remove(0));
}