#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("test isEmpty()", "[LimitedSizeBag]"){

  LimitedSizeBag<int> lsb;

  REQUIRE(lsb.isEmpty());

  lsb.add(1);

  REQUIRE(!lsb.isEmpty());
}

TEST_CASE("test add()", "[LimitedSizeBag]") {

  LimitedSizeBag<int> lsb;

  for(int i = 0; i < 10; i++)
    REQUIRE(lsb.add(i));

  REQUIRE(lsb.getCurrentSize() == 10);
  REQUIRE(!lsb.add(10));
}

TEST_CASE("test copy constructor", "[LimitedSizeBag]") {

  LimitedSizeBag<int> lsb;

  for(int i = 0; i < 5; i++)
    lsb.add(i);

  REQUIRE(lsb.getCurrentSize() == 5);

  LimitedSizeBag<int> lsb2(lsb);

  REQUIRE(lsb2.getCurrentSize() == 5);
  for(int i = 0; i < 5; i++)
    REQUIRE(lsb2.contains(i));
}

TEST_CASE("test copy assignment operator", "[LimitedSizeBag]") {

  LimitedSizeBag<int> b, b2;
  for(int i = 0; i < 10; i++) 
    b.add(i);

  b2 = b;
  REQUIRE(b.getCurrentSize() == 10);

  for(int i = 0; i < 10; i++)
    REQUIRE(b.contains(i));
  
}

TEST_CASE("test remove()", "[LimitedSizeBag]") {

  LimitedSizeBag<int> b;

  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < 10; ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  REQUIRE(!b.remove(-1));
  
  for(int i = 0; i < 10; ++i){
    REQUIRE(b.remove(i));
  }
  REQUIRE(!b.remove(0));
}

TEST_CASE("Test contains", "[LimitedSizeBag]"){

  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(!b.contains(0));
	
    for(int i = 0; i < 10; ++i){
      REQUIRE(b.add(i));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }
    
    for(int i = 0; i < 10; ++i){
      REQUIRE(b.contains(i));
    }
    REQUIRE(!b.contains(-1));
  }
  
  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(!b.contains(0));
    
    for(int i = 0; i < 10; ++i){
      REQUIRE(b.add(-1));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }

    REQUIRE(b.contains(-1));
    REQUIRE(!b.contains(0));
  }
}

TEST_CASE("Test getFrequencyOf()", "[LimitedSizeBag]"){

  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(b.getFrequencyOf(0) == 0);
    
    for(int i = 0; i < 10; ++i){
      REQUIRE(b.add(i));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }
    
    for(int i = 0; i < 10; ++i){
      REQUIRE(b.getFrequencyOf(i) == 1);
    }
  }
  
  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    
    for(int i = 0; i < 10; ++i){
      REQUIRE(b.add(-1));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }

    std::size_t EXPECTED = 10;
    REQUIRE(b.getFrequencyOf(-1) == EXPECTED);
    REQUIRE(b.getFrequencyOf(0) == 0);
  }
}

TEST_CASE("Test clear", "[Bag]"){

  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
  b.clear();
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < 10; ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  b.clear();
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
  
}

