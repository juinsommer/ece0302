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

TEST_CASE( "Test Stack handout-0", "[XMLParser]" )
{
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success = false;
		for (int i=0; i<testSize; i++) {
			intStack.push(i);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
		for (int i = testSize-1; i>=0; i--) {
			REQUIRE(intStack.isEmpty() == false);
            int elem = intStack.peek();
			REQUIRE(elem == i);
            REQUIRE(intStack.isEmpty() == false);
			intStack.pop();
		}
        REQUIRE(intStack.isEmpty() == true);
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

TEST_CASE( "Test parseTokenizedInput()", "[XMLParser]" ) {
	
	XMLParser x;
	char c;
	string str;
	//checks entire xmlFile.txt
	ifstream inFile;
	inFile.open("./xmlFile.txt");
	while (!inFile.eof()) {
		inFile.get(c);
		str.push_back(c);
	}
	inFile.close();
	REQUIRE(x.tokenizeInputString(str));
	REQUIRE(x.parseTokenizedInput());

	//test for illegal characters
	XMLParser x2, x3, x4, x5, x6, x7, x8;
	string str1 = "<.startTag>content</startTag>";
	string str2, str3, str4, str5, str6, str7;
	REQUIRE(x2.tokenizeInputString(str1));
	REQUIRE(!x2.parseTokenizedInput());

	str2 = "<-startTag>content</-startTag>";
	REQUIRE(x3.tokenizeInputString(str2));
	REQUIRE(!x3.parseTokenizedInput());

	str3 = "<5startTag>content</5startTag>";
	REQUIRE(x4.tokenizeInputString(str3));
	REQUIRE(!x4.parseTokenizedInput());

	str4 = "<start.Tag>content</start.Tag>";
	REQUIRE(x5.tokenizeInputString(str4));
	REQUIRE(x5.parseTokenizedInput());

	str5 = "<start-Tag>content</start-Tag>";
	REQUIRE(x6.tokenizeInputString(str4));
	REQUIRE(x6.parseTokenizedInput());

	str6 = "<.startTag>content</.startTag>";
	REQUIRE(x7.tokenizeInputString(str6));
	REQUIRE(!x7.parseTokenizedInput());

	str7 = "< startTag>content</ startTag>";
	REQUIRE(x8.tokenizeInputString(str7));
	REQUIRE(!x8.parseTokenizedInput());
} 

TEST_CASE( "Test containsElementName()", "[XMLParser]") {
	XMLParser x;
	char c;
	string str;
	//checks entire xmlFile.txt
	ifstream inFile;
	inFile.open("./xmlFile.txt");
	while (!inFile.eof()) {
		inFile.get(c);
		str.push_back(c);
	}
	inFile.close();
	REQUIRE(x.tokenizeInputString(str));
	REQUIRE(x.parseTokenizedInput());
	REQUIRE(x.containsElementName("note"));
}

TEST_CASE( "Test frequencyElementName()", "[XMLParser]") {
	XMLParser x;
	char c;
	string str;
	//checks entire xmlFile.txt
	ifstream inFile;
	inFile.open("./xmlFile.txt");
	while (!inFile.eof()) {
		inFile.get(c);
		str.push_back(c);
	}
	inFile.close();
	REQUIRE(x.tokenizeInputString(str));
	REQUIRE(x.parseTokenizedInput());
	REQUIRE(x.frequencyElementName("heading") == 1);
	REQUIRE(x.frequencyElementName("Note") == 0);
	REQUIRE(x.frequencyElementName("note") == 2);
}

TEST_CASE( "Test clear()", "[XMLParser]") {
	XMLParser x;
	char c;
	string str;
	//checks entire xmlFile.txt
	ifstream inFile;
	inFile.open("./xmlFile.txt");
	while (!inFile.eof()) {
		inFile.get(c);
		str.push_back(c);
	}
	inFile.close();
	REQUIRE(x.tokenizeInputString(str));
	REQUIRE(x.parseTokenizedInput());
	
	x.clear();
	REQUIRE(!x.parseTokenizedInput());
	REQUIRE(!x.containsElementName("note"));
	REQUIRE(x.frequencyElementName("note") == 0);
	REQUIRE(x.returnTokenizedInput().empty());
}

TEST_CASE( "Test XMLParser tokenizeInputString Handout-1", "[XMLParser]" )
{
	// Create an instance of XMLParse
	XMLParser myXMLParser;
	string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
	bool success;
	success = myXMLParser.tokenizeInputString(testString);
	REQUIRE(success);
	std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
								TokenStruct{StringTokenType::START_TAG, std::string("Note")},
								TokenStruct{StringTokenType::START_TAG, std::string("From")},
								TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
								TokenStruct{StringTokenType::END_TAG, std::string("From")},
								TokenStruct{StringTokenType::START_TAG, std::string("To")},
								TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
								TokenStruct{StringTokenType::END_TAG, std::string("To")},
								TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();

	REQUIRE(result.size() == output.size());
	for (int i = 0; i < result.size(); i++) {
		REQUIRE(result[i].tokenType == output[i].tokenType);
		REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
	}
}

TEST_CASE( "Test XMLParser Final Handout-0", "[XMLParser]" )
{
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		ifstream myfile ("./TestFile.txt");
		std::string inputString((std::istreambuf_iterator<char>(myfile) ), (std::istreambuf_iterator<char>()) );

		bool success;
		success = myXMLParser.tokenizeInputString(inputString);
		REQUIRE(success);
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		REQUIRE(myXMLParser.containsElementName("catalog"));
		REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
		REQUIRE(myXMLParser.containsElementName("product"));
		REQUIRE(myXMLParser.frequencyElementName("product") == 1);
		REQUIRE(myXMLParser.containsElementName("catalog_item"));
		REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
		REQUIRE(myXMLParser.containsElementName("item_number"));
		REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
		REQUIRE(myXMLParser.containsElementName("size"));
		REQUIRE(myXMLParser.frequencyElementName("size") == 6);
		REQUIRE(myXMLParser.containsElementName("color_swatch"));
		REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}

TEST_CASE( "Test XMLParser parseTokenizedInput Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}
TEST_CASE( "Test XMLParser tokenizeInputString Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test Stack handout-1", "[XMLParser]" )
{
	   Stack<char> charStack;
       std::string s("Hello world");
       int i = 1;
       for (auto c:s) {
           charStack.push(c);
           REQUIRE(charStack.size() == i);
           i++;
       }
       for (i = 0; i < 5; i++) {
           REQUIRE(charStack.isEmpty() == false);
           char c = charStack.peek();
           REQUIRE(c == s[s.length()-1-i]);
           REQUIRE(charStack.isEmpty() == false);
           charStack.pop();
       }
       REQUIRE(charStack.size() == 6);
       charStack.clear();
       REQUIRE(charStack.isEmpty() == true);      
}