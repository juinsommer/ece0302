#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}
// converts postfix expression to prefix expression
// form of preFix expression is <prefix> = <identifier>|<operator><prefix><prefix>
void convert(string &postfix, string &prefix) {

  int postLength = postfix.length();  //postLength stores length of postFix expression
  char ch = postfix.back(); //ch stores last character in postFix expression
  string tempPost;

  if(postfix.length() == 1) //if postfix expression is a single character
    prefix += ch;

  else //if last character is an operator
  {
    int endFirst = endPost(postfix, postLength); // find end of postfix1
    string temp = postfix.substr(endFirst + 1, postLength - 1);
  
    if(isoperator(ch))
      prefix += ch; //append operator to front of prefix expression

    convert(temp, prefix);  //recursively convert postfix1 into prefix form

    if(!isoperator(ch))
      prefix += ch;
  }
}
