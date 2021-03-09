#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include <fstream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

// TODO Implement tests of your Stack class and XMLParser class here

TEST_CASE( "Test Bag add", "[XMLParser]" )
{
	   INFO("Hint: testing Bag add()");
		// Create a Bag to hold ints
		Bag<int> intBag;
		int testSize = 2;
		int bagSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intBag.add(i);
			REQUIRE(success);
			bagSize = intBag.size();
			success = (bagSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack push", "[XMLParser]" )
{
	   INFO("Hint: testing Stack push()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 3;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test XMLParser tokenizeInputString", "[XMLParser]" )
{
		//checks content, start, and end tag recognition
		XMLParser myXMLParser;
		string testString = "<startTag>content</endTag>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);

		//checks for declaration recognition
		XMLParser x, x2, x3;
		string str = "<?xml version=\"1.0\"?>";
		REQUIRE(x.tokenizeInputString(str));
		REQUIRE(x.returnTokenizedInput()[0].tokenType == 5);
		REQUIRE(x.returnTokenizedInput()[0].tokenString == "xml version=\"1.0\"");

		string str2, str3;
		char c;
		//checks entire xmlFile.txt
		ifstream inFile;
		inFile.open("./xmlFile.txt");
		while (!inFile.eof()) {
			inFile.get(c);
			str2.push_back(c);
		}
		inFile.close();
		REQUIRE(x2.tokenizeInputString(str2));
		//end xmlFile check

		//checks for invalid token with nested angle brackets
		str3 = "<a<b>>";
		REQUIRE(!x3.tokenizeInputString(str3));
}

