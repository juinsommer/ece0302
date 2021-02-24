#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

#include <string>
#include <vector>

int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

TEST_CASE( "Test add(const string &)", "[FindPalindrome]" )
{

	FindPalindrome b, b2, b3;
	std::string str = "";
	for(int i = 1; i <= 3; ++i) {
		str.append("a");
		REQUIRE(b.add(str));
	}
	REQUIRE(b.number() == factorial(3));

	REQUIRE(b2.add("Odd"));
	REQUIRE(b2.add("Never"));
	REQUIRE(b2.add("Even")); 

	REQUIRE(b3.add("abba"));
	REQUIRE(!b3.add("AbbA"));
	REQUIRE(!b.add("kayak1"));
	REQUIRE(!b.add("Ace1Hardware"));
	REQUIRE(!b.add("NeverOddOrEven!"));

	REQUIRE(b3.number() == 1);

}

TEST_CASE( "Test add(const vector<string> &)", "[FindPalindrome]")
{
	FindPalindrome b, b2, b3, b4, b5, b6, b7;
	std::vector<std::string> strVect = {"Was", "it", "a", "car", "or", "a", "cat", "I", "saw" };
	REQUIRE(b.add(strVect));
	REQUIRE(!b.add("was"));

	std::vector<std::string> strVect2 = {"aaaa", "this", "is", "my", "swamp"};
	REQUIRE(!b2.add(strVect2));

	std::vector<std::string> strVect3 = {"Never", "Odd", "or", "Even"}, strVect4;
	REQUIRE(b3.add(strVect3));
	REQUIRE(b3.number() == 1);
	strVect4 = {"never"};
	REQUIRE(!b3.add(strVect4));

	std::vector<std::string> strVect5 = {"Never", "Odd", "or"}, strVect6 = {"Even"}, strVect7 = {"Kayak1!"};
	REQUIRE(!b4.add(strVect5));
	REQUIRE(b4.number() == 0);
	REQUIRE(b4.add(strVect6));
	REQUIRE(b4.number() == 1);
	REQUIRE(!b4.add(strVect7));

	std::vector<std::string> strVect8 = {"Never", "Even"}, strVect9 = {"Odd", "or "};
	REQUIRE(b5.add(strVect8));
	REQUIRE(!b5.add(strVect9));

	std::vector<std::string> strVect10 = {"a", "aa", "aaa" , "aaaa"};
	REQUIRE(b6.add(strVect10));
	REQUIRE(b6.number() == factorial(4));

}

TEST_CASE( "Test cutTest1()", "[FindPalindrome]")
{
	FindPalindrome b, b2, b3, b4, b5;
    std::vector<std::string> strVect = {"Was", "it", "a", "car", "or", "a", "cat", "I", "saw" };

	REQUIRE(b.cutTest1(strVect));

	std::vector<std::string> strVect2 = {"oh", "hi", "Mark"};
	REQUIRE(!b2.cutTest1(strVect2));

	std::vector<std::string> strVect3 = {"yo", "banana", "boy"};
	REQUIRE(b3.cutTest1(strVect3));

	std::vector<std::string> strVect4 = {"Dammit", "Im", "mad"};
	REQUIRE(b4.cutTest1(strVect4));

	std::vector<std::string> strVect5 = {"Never", "odd", "or"};
	REQUIRE(!b5.cutTest1(strVect5));
}

TEST_CASE( "Test cutTest2()", "[FindPalindrome]") 
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

	FindPalindrome b4; 
	std::vector<std::string> str7, str8;

	str7 = {"Odd", "Even"};
	str8 = {"Never", "or"};
	REQUIRE(b4.cutTest2(str8, str7));
}

TEST_CASE("Test clear()", "[FindPalindrome]") {
	FindPalindrome f, f2;
	std::string str;
	for(std::size_t i = 0; i <= 3; i++) {
		str.append("a");
		REQUIRE(f.add(str));
	}
	f.clear();
	REQUIRE(f.number() == 0);
	REQUIRE(f.toVector().empty());

	std::vector<std::string> strVect = {"As", "I", "pee", "sir", "I", "see", "Pisa"};
	REQUIRE(f2.add(strVect));
	f2.clear();
	REQUIRE(f2.number() == 0);
	REQUIRE(f2.toVector().empty());
}