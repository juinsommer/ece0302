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
	//base case if currentStringVector is empty
	if(currentStringVector.empty()) {

		std::string tempCandStr;
		//append each string from vector into one string
		for(auto i : candidateStringVector) 
			tempCandStr.append(i);
		
		if(isPalindrome(tempCandStr)) //if it is a palindrome add string to vector
			palindromeVect.push_back(candidateStringVector);
	}
	
	else {
		//interate over the size of currentStringVector to get every combination of strings
		for(std::size_t i = 0; i < currentStringVector.size(); i++) {
			vector<string> tempCandidateVect(candidateStringVector);
			vector<string> tempCurrentVect(currentStringVector);
			
			//remove one element each iteration in ascending order
			tempCurrentVect.erase(tempCurrentVect.begin() + i);
			//push back the ith element of currentString vector to tempCandidate
			tempCandidateVect.push_back(currentStringVector[i]);
			//if cutTest2 is not passed, break from this branch
			if(!cutTest2(tempCandidateVect, tempCurrentVect))
				return;
			recursiveFindPalindromes(tempCandidateVect, tempCurrentVect);
		}
	}
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
FindPalindrome::FindPalindrome() {}

FindPalindrome::~FindPalindrome() { clear(); }

//returns number of palindromes in vector
int FindPalindrome::number() const { return palindromeVect.size(); } 

//clears vector storing all sentence palindromes 
void FindPalindrome::clear() { palindromeVect.clear();}

//checks if sentence palindrome is possible or not given that it satisfies property#1
bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	std::string tempStr;

	//append each string in vector to tempStr
	for(auto i : stringVector)
		tempStr.append(i);

	convertToLowerCase(tempStr);

	int letters[26] = {0}; //array to store frequency of any character in alphabet
	int middle = (tempStr.size())/2; //find middle character at middle of sentence
	int i = 0, j; //counters for while loop
	
	convertToLowerCase(tempStr);
	//iterate through the string to count frequency each character appears in string
	while(tempStr[i] != '\0') {
		//if contents are characters a - z
		if(tempStr[i] >= 'a' && tempStr[i] <= 'z') {
			j = tempStr[i] - 'a'; //gets character's position in alphabet
			++letters[j]; //increments frequency of character 
		}
		++i;
	}
	//if the number of characters in sentence is even, all characters must appear 
	//an even amount of times
	if(tempStr.length() % 2 == 0) {
		//check if the frequency of characters is odd
		for(std::size_t i = 0; i < 26; i++) {
			if(letters[i] % 2 != 0)
				return false;	
		}	
	}
	//if the number of characters in sentence is odd then each character must appear
	//an even amount of times except for middle character unless they are the same
	//as middle character
	else {
		for(std::size_t i = 0; i < 26; i++) {
			//if frequency of char is odd and not middle char
			if(letters[i] % 2 != 0 && i != (tempStr[middle] - 'a'))
				return false;
		}
	} //end else

	return true;
}

//checks if palindrome is possible or not given that it satifies property 2
bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	std::string tempStr1, tempStr2, smaller, larger;

	//append strings in both vectors to two separate strings
	for(auto i : stringVector1)
		tempStr1.append(i);

	for(auto i : stringVector2)
		tempStr2.append(i);

	convertToLowerCase(tempStr1);
	convertToLowerCase(tempStr2);

	//determine which string is longer and assign
	if(tempStr2.length() > tempStr1.length()) {
		smaller = tempStr1;
		larger = tempStr2;
	}
	else {
		smaller = tempStr2;
		larger = tempStr1;
	}

	int freq1[26] = {0}, freq2[26] = {0}, count1 = 0, count2 = 0, j, k;
	//determine the frequency of each character in smaller string
	while(smaller[count1] != '\0') {

		if(smaller[count1] >= 'a' && smaller[count1] <= 'z') {
			j = smaller[count1] - 'a'; 
			++freq1[j];
		}
		++count1;
	}
	//determine the frequency of each character in larger string
	while(larger[count2] != '\0') {
		if(larger[count2] >= 'a' && larger[count2] <= 'z') {
			k = larger[count2]- 'a';
			++freq2[k];
		}
		++count2;
	}
	//if the frequency of each character in the larger string is less than
	//the frequency of the smaller string then return false
	for(std::size_t i = 0; i < 26; i++) {
		if(freq2[i] < freq1[i])
			return false;
		else
			return true;
	}

	return true;
}

bool FindPalindrome::add(const string & value)
{
	std::string tempStr = value;
	std::vector<std::string> tempCurrentVect(currentVect);

	//iterate over string to check if each char is valid
	for(const char c : tempStr) 
		//isalpha() checks if char is any letter
		if(!std::isalpha(c))
			return false;
			
	convertToLowerCase(tempStr);
	//check if there are duplicates
	for(auto i : tempCurrentVect) {
		convertToLowerCase(i);
		if(tempStr.compare(i) == 0)
			return false;
	}
	currentVect.push_back(value); //push back to private member variable 

	std::vector<std::string> tempCandVect; //empty temp vector 
	clear();
	recursiveFindPalindromes(tempCandVect, currentVect);
	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	std::vector<string> tempVect(stringVector); //copy into a temp vector
	std::string tempStr; //temp to store sentence in string vector

	//iterates over copy of stringVector
	for(auto i : tempVect) {
		convertToLowerCase(i); //convert to lowercase to compare
		for(auto j : currentVect) {
			convertToLowerCase(j);
			if(i == j) //if there are duplicates return false
				return false;
		}
		tempStr.append(i); //append each string in vector
		//checks if there are any illegal characters
		for(const char c : tempStr) {
			if(!std::isalpha(c))
				return false;
		}
	}
	//add each string to private member variable
	for(auto i : stringVector)
		currentVect.push_back(i);

	std::vector<std::string> tempCandVect; //empty temp vector

	if(cutTest1(currentVect)) { //if stringVector passes cutTest1
		clear();
		recursiveFindPalindromes(tempCandVect, currentVect);	
		return true; 
	}
	return false;
}
//returns vector of vectors containing all sentence palindromes
vector< vector<string> > FindPalindrome::toVector() const
{
	vector<vector<string>> tempVector(palindromeVect);

	return tempVector;
}

