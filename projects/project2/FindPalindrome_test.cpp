#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

#include <string>
#include <vector>

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test FindPalindrome add a non-allowable word", "[FindPalindrome]" )
{
	INFO("Hint: add a single non-allowable word");
	FindPalindrome b;
	REQUIRE(b.add("abba"));
	REQUIRE(!b.add("AbbA"));
	REQUIRE(!b.add("kayak1"));
	REQUIRE(!b.add("Ace1Hardware"));
}

TEST_CASE( "Test FindPalindrome add(const vector<string> &)", "[FindPalindrome]")
{
	FindPalindrome b, b2;
	std::vector<std::string> strVect = {"Was", "it", "a", "car", "or", "a", "cat", "I", "saw" };
	REQUIRE(b.add(strVect));

	std::vector<std::string> strVect2 = {"aaaa", "this", "is", "my", "swamp"};
	REQUIRE(!b2.add(strVect2));
}