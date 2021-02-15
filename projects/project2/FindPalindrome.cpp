#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	// TODO need to implement this recursive function!

}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------
/*FindPalindrome::FindPalindrome()
{
	
}

FindPalindrome::~FindPalindrome()
{
	
} */

int FindPalindrome::number() const
{
	return numPalindromes;
}

void FindPalindrome::clear()
{
	// TODO need to implement this...
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	// TODO need to implement this...
	return false;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	// TODO need to implement this...
	return false;
}

bool FindPalindrome::add(const string & value)
{
	bool validStr; //to store validity of string "value"
	string tempStr = value;

	//iterate over string to check if each char is valid
	for(const char c : value) 
		//isalpha() checks if char is any letter
		validStr = (!isalpha(c)) ? false : true;
			
	convertToLowerCase(tempStr); //convert to lowercase to compare
	validStr = (tempStr.compare(objStr) == 0) ? false : true;
	
	if(validStr) { //if the string is valid, then append
		objStr.append(value);
		return (isPalindrome(objStr)); //check if palindrome 
	}

	else 
		return false;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	bool validStr = true; //to store validity of string "value"
	vector<string> tempVect(stringVector);

	for(size_t i = 0; i < stringVector.size(); i++) {
		string tempStr = stringVector[i];
		for(const char c : tempStr)
			//isalpha() checks if char is any letter
			if(!isalpha(c))
				validStr = false;

		for(auto i : tempStr) {
			convertToLowerCase(tempStr); //convert to lowercase to compare
			if(tempStr.compare(objStr) == 0)
				validStr = false;
		}
	}

	if(validStr) {
		for(auto i : stringVector)
			objStr.append(i);

		return (isPalindrome(objStr));
	}
	else
		return false;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	// TODO need to implement this...
	vector<vector<string>> returnThingie;
	return returnThingie;
}

