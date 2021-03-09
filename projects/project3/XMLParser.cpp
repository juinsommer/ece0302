// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
}  // end destructor

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	//iterate over size of input string
	for(std::size_t i = 0; i < inputString.size(); i++) {
		TokenStruct t, t2; //declare two tokenStruct objects locally every iteration
		//if char is opening angle bracket
		if(inputString[i] == '<') {
			int j = i;
			while(inputString[++j] != '>') { //grab the substring until closing bracket
				if(inputString[j] == '<') //returns false if brackets are nested
					return false;
				t.tokenString += inputString[j]; //append char to tokenString
			}
			//assign token type based on 1st and or last char of substring
			if(t.tokenString.front() == '/') {
				t.tokenString.erase(0,1);
				t.tokenType = END_TAG;
			}
			else if(t.tokenString.front() == '?' && t.tokenString.back() == '?') {
				t.tokenString.erase(0,1);
				t.tokenString.pop_back();
				t.tokenType = DECLARATION;
			}
			else if(t.tokenString.back() == '/') {
				t.tokenString.pop_back();
				t.tokenType = EMPTY_TAG;
			}
			else if(isalpha(t.tokenString.front()) && isalpha(t.tokenString.back()))
				t.tokenType = START_TAG;
	
			tokenizedInputVector.push_back(t); //push tokenStruct object to vector
		}
		//if char is closing angle bracket and next char is not end of string
		if(inputString[i] == '>' && inputString[i + 1] != '\0') {
			int k = i;
			while(inputString[++k] != '<') { //grab substring until next opening bracket
				if(inputString[k] == '>') //checks for nested brackets
					return false;
				t2.tokenString += inputString[k];
			}
			if(t2.tokenString.front() != '\n') { //if 1st char of token str is not a new line
				t2.tokenType = CONTENT;
				tokenizedInputVector.push_back(t2);
			}
		}
	}
	for(auto i : tokenizedInputVector)
		std::cout << "token string: " << i.tokenString 
				  << std::endl << "token type: " << i.tokenType
				  << std::endl << std::endl;

	return true;
}  // end

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(std::string input)
{
	return input;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	
	return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	return false;
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	return -1;
}

