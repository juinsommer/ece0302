// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include <cctype>
#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	parseStack = new Stack<std::string>;
	elementNameBag = new Bag<std::string>;

}  //end default constructor

//class destructor
XMLParser::~XMLParser() 
{ 
	clear();
	delete parseStack;
	delete elementNameBag;
}  // end destructor

//deletes attributes from a start or empty tag
static std::string deleteAttributes(std::string input)
{
	std::string temp;
	for(const char c: input) {
		//if character is a space or terminating escape sequence and 
		//1st character is not a string then break
		//(does not break if 1st char is space because input validation for tags is done in parse method)
		if(isspace(c) || c == '\0' && !isspace(temp.front()))
			break;

		  temp.push_back(c);
	}
	return temp;
}

// breaks input string into tokens and deletes attributes from start and empty tags
// if they exist.
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	//iterate over size of input string
	for(std::size_t i = 0; i < inputString.size(); i++) {
		TokenStruct t, t2; //declare two tokenStruct objects locally every iteration
	
		//if char is opening angle bracket
		if(inputString[i] == '<') {
			int j = i;
			while(inputString[++j] != '>') { //grab the substring until closing bracket
				if(inputString[j] == '<') { //returns false if brackets are nested
					clear();
					return false;
				}
				t.tokenString += inputString[j]; //append char to tokenString
			} //end while

			//assign token type based on 1st and or last char of substring
			if(t.tokenString.front() == '/') {
				t.tokenString.erase(0,1); //erase backslash
				t.tokenType = END_TAG;
			}
			else if(t.tokenString.front() == '?' && t.tokenString.back() == '?') {
				t.tokenString.erase(0,1); //erase 1st question mark
				t.tokenString.pop_back(); //erase 2nd question mark
				t.tokenType = DECLARATION;
			}
			else if(t.tokenString.back() == '/') {
				t.tokenString.pop_back(); //erase backslash
				t.tokenString = deleteAttributes(t.tokenString); 
				t.tokenType = EMPTY_TAG;
			}
			else if(isalpha(t.tokenString[0]) || isdigit(t.tokenString[0])) {
				t.tokenType = START_TAG;
				t.tokenString = deleteAttributes(t.tokenString);
			}
			if(t.tokenType != DECLARATION) {
				//checks if first character is an illegal 1st character
				if(t.tokenString[0] == '.' || t.tokenString[0] == '-' || isdigit(t.tokenString[0]) || isspace(t.tokenString[0])) {
					clear();
					return false;
				}
				//if string not a single character
				if(t.tokenString.size() > 1) {
					// iterate over string starting after 1st character
					for(const char c : t.tokenString.substr(1, t.tokenString.length())) {
						// if is an illegal character
						if(!isalpha(c) && c != '.' && c != '-' && c != '_' && !isdigit(c) || isspace(c)) {
							clear();
							return false;
						} //end if
					} //end for
				} //end if
			} //end if
			tokenizedInputVector.push_back(t); //push tokenStruct object to vector
		}
		//if char is closing angle bracket and next char is not end of string
		if(inputString[i] == '>' && inputString[i + 1] != '\0') {
			int k = i;
			while(inputString[++k] != '<' && inputString[k + 1] != '\0') { //grab substring until next opening bracket
				if(inputString[k] == '>') { //checks for nested brackets
					clear();
					return false;
				}
				if(isalpha(inputString[k]) || isdigit(inputString[k]) || inputString[k] == ' ')
					t2.tokenString += inputString[k];
			}
			if(t2.tokenString.find_first_not_of(' ') != std::string::npos) { //if token string is not empty
				t2.tokenType = CONTENT;
				tokenizedInputVector.push_back(t2);
			}
		}//end if
	}//end for

	return true;
}

// checks if file follows BPG, there are no illegal characters, illegal placement of characters
// and sets element names
bool XMLParser::parseTokenizedInput()
{
	//if there are no tokens to parse
	if(tokenizedInputVector.empty())
		return false;
	//iterate over vector of token objects
	for(auto i : returnTokenizedInput()) {
		std::string matchTag, temp;
		bool isMatch = false;
		//switch passed with token type of each object in vector
		switch(i.tokenType) {
			case START_TAG:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
				temp = i.tokenString;
				parseStack->push(temp); //push string to stack
				break;

			case END_TAG:
				if(parseStack->isEmpty()) {
					clear();
					return false;
				}

				temp = i.tokenString;
				
				matchTag = parseStack->peek(); //matching tag is assigned to string at top of stack
				isMatch = (temp == matchTag) ? true : false; 

				if(!isMatch) { //if tags don't match
					clear();
					return false;
				}
				
				parseStack->pop();
				elementNameBag->add(temp); //add element name to list
				break;

			case EMPTY_TAG:
				//if empty tag is the first tag
				if(i.tokenType == returnTokenizedInput()[0].tokenType) {
					clear();
					return false;
				}
				temp = i.tokenString;
				elementNameBag->add(temp);
				break;

			case CONTENT:

				if(parseStack->isEmpty()) {
					clear();
					return false;
				}

			default:
				break;
		} //end switch
	} //end for 
	if(!parseStack->isEmpty()) {
		clear();
		return false;
	}
	return true;
}

//clears stack, list of element names, and token vector
void XMLParser::clear()
{
	parseStack->clear();
	elementNameBag->clear();
	tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const { return tokenizedInputVector; }

//checks if element name exists in xml file
bool XMLParser::containsElementName(const std::string &inputString) const
{
	bool doesContain = false;
	if(!returnTokenizedInput().empty() && !elementNameBag->isEmpty()) {
		doesContain = elementNameBag->contains(inputString) ? true : false;
	}
	else
		throw logic_error("returnTokenizedInput() is empty or elementNameBag is empty");

	return doesContain;
}

//checks the frequency of an element name in xml file
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	if(!returnTokenizedInput().empty() && !elementNameBag->isEmpty()) 
		return elementNameBag->getFrequencyOf(inputString);

	else
		throw logic_error("returnTokenizedInput() is empty or elementNameBag is empty");
}

