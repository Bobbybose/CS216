/* 
 * File: smartReverse.cpp
 * Purpose: provide the implementation of the smartReverse class
 *
 * Author: Bobby Bose
 *
 */

#include <stack>
#include "smartReverse.h"
#include <iostream>

// default constructor
smartReverse::smartReverse()
{	
}

// constructor: initialize str with ini_str passing as a parameter
smartReverse::smartReverse(string ini_str)
{
	str=ini_str;
}

// return the current value of the private data member: str
string smartReverse::getString() const
{
	return str;
}

// set the value of str to be the passed in parameter input_str
void smartReverse::setString(string input_str)
{
	str=input_str;
}

// return a reversed string from str
// using a loop to implement
// Note that str has not been changed
string smartReverse::rev() const
{
	string temp="";

	for(int i=str.length()-1; i>=0; i--){
		temp=temp+str.at(i);
	}

	return temp;	
}

// return a reversed string from str
// using recursion to implement
// Note that str has not been changed
string smartReverse::rev_recursive() const
{
	if(str=="")
		return "";
	return str[str.length()-1]+smartReverse(str.substr(0,str.length()-1)).rev_recursive();
}

// return a reversed string from str
// using a stack to implement
// Note that str has not been changed
string smartReverse::rev_stack() const
{
	stack<string> ans;
	string answer="";	
	string temp="";
	for(int i=0; i<str.length(); i++){
		temp=str.at(i);
		ans.push(temp);
	}		

	for(int i=0; i<str.length(); i++){
		answer=answer+string(ans.top());
		ans.pop();
	}		
	return answer;
}

