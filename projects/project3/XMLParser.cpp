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

}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser() 
{ 
	clear();
	delete parseStack;
	delete elementNameBag;
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
			else
				t.tokenType = START_TAG;
	
			tokenizedInputVector.push_back(t); //push tokenStruct object to vector
		}
		//if char is closing angle bracket and next char is not end of string
		if(inputString[i] == '>' && inputString[i + 1] != '\0') {
			int k = i;
			while(inputString[++k] != '<') { //grab substring until next opening bracket
				if(inputString[k] == '>') //checks for nested brackets
					return false;
				if(!isblank(inputString[k]) && inputString[k] != '\n' && !isspace(inputString[k])) 
					t2.tokenString += inputString[k];
			}
			if(!t2.tokenString.empty()) {
				t2.tokenType = CONTENT;
				tokenizedInputVector.push_back(t2);
			}
		}//end if
	}//end for
	return true;
}
//deletes attributes from a start or empty tag
static std::string deleteAttributes(std::string input)
{
	std::string temp;
	for(const char c: input) {
		if(std::isspace(c) || c == '\0')
			break;

		  temp.push_back(c);
	}
	return temp;
}

/*static bool isIllegalChar(const char c) {
	return ((c == '!') || (c == '#') || (c == '"') || (c == '$') || (c == '%') 
			|| (c == '\'') || (c == '(') || (c == ')') || (c == '*') || (c == '+')
			|| (c == ',') || (c == '/') || (c == ';') || (c == '<') || (c == '>')
			|| (c == '=') || (c == '@') || (c == '^')); 
}*/
// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	if(tokenizedInputVector.empty())
		return false;

	for(auto i : returnTokenizedInput()) {
		std::string matchTag, temp;
		bool isMatch = false;

		switch(i.tokenType) {
			case START_TAG:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
				temp = i.tokenString;
				if(temp[0] == '.' || temp[0] == '-' || isdigit(temp[0]) || isspace(temp[0]))
					return false;

				temp = deleteAttributes(i.tokenString);
				for(const char c : temp.substr(1, temp.length())) {
					if(!isalpha(c) && c != '.' && c != '-' && !isdigit(c) || isspace(c))
						return false;
				}
				parseStack->push(temp);
				break;

			case END_TAG:
				if(parseStack->isEmpty())
					return false;
				temp = i.tokenString;
				if(temp[0] == '.' || temp[0] == '-' || isdigit(temp[0]) || isspace(temp[0]))
					return false;

				for(const char c : temp.substr(1, temp.length())) {
					if(!isalpha(c) && c != '.' && c != '-' && !isdigit(c) || isspace(c))
						return false;
				}
				matchTag = parseStack->peek();
				isMatch = (temp == matchTag) ? true : false;

				if(!isMatch)
					return false;
				
				parseStack->pop();
				elementNameBag->add(temp);
				break;

			case EMPTY_TAG:
				temp = i.tokenString;
				if(temp[0] == '.' || temp[0] == '-' || isdigit(temp[0]) || isspace(temp[0]))
					return false;
	
				temp = deleteAttributes(i.tokenString);
				for(const char c : temp.substr(1, temp.length())) {
					if(!isalpha(c) && c != '.' && c != '-' && !isdigit(c) || isspace(c))
						return false;
				}
				elementNameBag->add(temp);
				break;

			default:
				break;
		} //end switch
		
	} //end for 
	return true;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	parseStack->clear();
	elementNameBag->clear();
	tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const { return tokenizedInputVector; }

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	bool doesContain = false;
	if(!elementNameBag->isEmpty()) {
		doesContain = elementNameBag->contains(inputString) ? true : false;
	}
	return doesContain;
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	return elementNameBag->getFrequencyOf(inputString);
}

