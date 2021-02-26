#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

int main()
{
    FindPalindrome f, f2;
	
	cout << "\n******* Project 1 Main *********\n\n";

	f2.add("murder");
	f2.add("jar");
	f2.add("a");
	f2.add("red");
	f2.add("for"); 
	f2.add("of");
	f2.add("rum");

	vector<string> str = {"Murder", "for", "a", "jar", "of", "red", "rum"};
	f.add(str);

	cout << endl;
	cout << "\n******* Project 1 Main *********\n\n"; 
	cout << "add(const vector<string> &)\n";
	cout << "\nNumber of sentence palindromes are:  " << f.number() << endl;
	cout << "\nThe sentence palindromes are:" << endl;
	vector<vector<string>> vectorList = f.toVector();
	for (int i=0; i<vectorList.size(); i++) {
		for (int j=0; j<vectorList[i].size(); j++) {
			cout << vectorList[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "\n******* Project 1 Main *********\n\n"; 
	cout << "add(const string &)\n";
	cout << "\nNumber of sentence palindromes are:  " << f2.number() << endl;
	cout << "\nThe sentence palindromes are:" << endl;
	vector<vector<string>> vectorList2 = f2.toVector();
	for (int i=0; i<vectorList2.size(); i++) {
		for (int j=0; j<vectorList2[i].size(); j++) {
			cout << vectorList2[i][j] << " ";
		}
		cout << endl;
	} 
	cout << endl;
	cout << "\n******* Project 1 Main *********\n\n";

	return 0;

}

