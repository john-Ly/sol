/*
  C++ Program to check for balanced parentheses in an expression using stack.
  Given an expression as string comprising of opening and closing characters
  of parentheses - (), curly braces - {} and square brackets - [], we need to
  check whether symbols are balanced or not.
*/

/*
  some thoughts: @TODO
  1. other token like html tags "<*>" "</*>" ---- not single character
       http://stackoverflow.com/questions/11552209/using-stacks-to-check-balance-of-html-tags
  2. when check is not balanced, how to find the location of the first imbalanced token
  3. fixed intelligently
  4. should custom stack ADT ?
  5. without stack ?
       http://stackoverflow.com/questions/18482654/to-check-if-paranthesis-are-balanced-without-stack
  6. ***some question***:
     "abcdedcba" such string can use stack to check ? ...

  analysis:
  1. Time Compexity: O(n)
  2. Auxiliary Space: O(n) for stack

*/
#include <iostream>
#include <stack>   // seq_stack & link_stack getTop return false or true
#include <string>
#include <algorithm>
using std::cout;
using std::cin;

// Function to check whether two characters are opening
// and closing of same type.
bool ArePair(char opening,char closing) {
	if(opening == '(' && closing == ')') return true;
	else if(opening == '{' && closing == '}') return true;
	else if(opening == '[' && closing == ']') return true;
	else if(opening == '<' && closing == '>') return true;
	return false;
}

/*
The flow would be:
 - If the token is an open token, push it onto the stack.
 - If the token is a close token, check if the top of the stack is the corresponding open-token.
     If it is, then pop the stack as you found them balanced.
     If it is not, then it's an error.
 - end of file, if the stack is not empty, report an error.
 (last unclosed, first closed)

 ref: https://gist.github.com/mycodeschool/7207410
*/

bool AreParanthesesBalanced(std::string exp) {
	std::stack<char>  S;
	for(int i =0;i<exp.length();i++) {
		if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
			S.push(exp[i]);
		else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
			if(S.empty() || !ArePair(S.top(),exp[i]))
				return false;
			else
				S.pop();
		}
	}
	return S.empty();
}

// other test method, more simple
bool wellMatched(const std::string& formula) {
	//
	const std::string opening("({["), closing(")}]");
	std::stack<char> openStack;
	for(int i=0; i<formula.size(); i++)
		if(opening.find(formula[i]) != -1)
			openStack.push(formula[i]);
		else {
			if(openStack.empty()) return false;
			if(opening.find(openStack.top()) != closing.find(formula[i]) )
				return false;
			openStack.pop();
		}
	return openStack.empty();
}

int main() {
	/*Code to test the function AreParanthesesBalanced*/
	std::string expression;
	cout<<"Enter an expression:  "; // input expression from STDIN/Console
	cin>>expression;
//	if(AreParanthesesBalanced(expression))
	if(wellMatched(expression))
		cout<<"Balanced\n";
	else
		cout<<"Not Balanced\n";
}
