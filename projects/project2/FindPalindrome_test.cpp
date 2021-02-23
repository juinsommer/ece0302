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

TEST_CASE( "Test cutTest1()", "[FindPalindrome]")
{
	FindPalindrome b, b2, b3, b4;
    std::vector<std::string> strVect = {"Was", "it", "a", "car", "or", "a", "cat", "I", "saw" };

	REQUIRE(b.cutTest1(strVect));

	std::vector<std::string> strVect2 = {"oh", "hi", "Mark"};
	REQUIRE(!b2.cutTest1(strVect2));

	std::vector<std::string> strVect3 = {"yo", "banana", "boy"};
	REQUIRE(b3.cutTest1(strVect3));

	std::vector<std::string> strVect4 = {"Dammit", "Im", "mad"};
	REQUIRE(b4.cutTest1(strVect4));
}

TEST_CASE( "Test cutTest2()", "FindPalindrome]") 
{
	FindPalindrome b;
	std::vector<std::string> str1, str2;

	str1 = {"As", "I", "pee"};
	str2 = {"sir", "I", "see", "Pisa"};

	REQUIRE(b.cutTest2(str1, str2));

	FindPalindrome b2;
	std::vector<std::string> str3, str4;

	str3 = {"Was", "it", "a", "car"};
	str4 = {"or", "a", "cat", "I", "saw" };
	REQUIRE(b2.cutTest2(str4, str3));

	FindPalindrome b3;
	std::vector<std::string> str5, str6;

	str5 = {"this", "project", "is"};
	str6 = {"very", "annoying"};
	REQUIRE(!b3.cutTest2(str5, str6));
}