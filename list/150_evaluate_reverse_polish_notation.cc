/*
  binary operator: just two operands

  infix: <operand> <operator> <operand> 2+3
  Order of operation:
  1) parentheses () {} []
  2) exponents                     <-   right associative
  3) multiplication and division   ->   left associative
  4) addition and substraction     ->

  easy to parse and low costly stored in computer
  prefix:  <operator> <operand> <operand> + 2 3
  postfix: <operand> <operand> <operator> 2 3 +
  Reverse Polish notation (RPN)


  Evaluation Of postfix Expression in C++
  Input Postfix expression must be in a desired format.
  Operands must be integers and there should be space in between two operands.
  Only '+'  ,  '-'  , '*' and '/'  operators are expected.

  b. 利用栈 进行字符串的翻转

*/

#include<iostream>
#include<stack>
#include<string>
using namespace std;

namespace ReverseString {

void reverseString(char *C, int n) {
    stack<char> S;

    for(int i=0; i<n; i++){ S.push(C[i]); }
    for(int i=0; i<n; i++){ C[i] = S.top(); S.pop(); }
}

void reverseString(vector<char>& s) {
    for(int i = 0; i < s.size() / 2; i++) swap(s[i], s[s.size() - i - 1]);
}

/*
time complexity: O(n)
space complexity: O(n)

actually, better solution: use i,j to mark the begin and end,
  while(i<=j){
          swap(C[i], C[j]);
          i++;
          j--;
  }
don't need extral memory, time O(n/2) = O(n)
*/
}

// Function to evaluate Postfix expression and return output
int EvaluatePostfix(string expression);

// Function to perform an operation and return output.
int PerformOperation(char operation, int operand1, int operand2);

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C);

// Function to verify whether a character is numeric digit.
bool IsNumericDigit(char C);

int main() {
	string expression;
	cout<<"Enter Postfix Expression \n";
	getline(cin,expression);
	int result = EvaluatePostfix(expression);
	cout<<"Output = "<<result<<"\n";
}

// Function to evaluate Prefix expression and return output
int EvaluatePrefix(string expression){}
// scan from right to left
// top will the first operand, then second

// 处理 一个有效的p后缀表达式( 处理operator 操作符 和 operand操作数)
// Function to evaluate Postfix expression and return output
int EvaluatePostfix(string expression) {
	stack<int> S;
	for(int i = 0;i< expression.length();i++) {

		// Scanning each character from left.
		// If character is a delimitter, move on.
		if(expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if(IsOperator(expression[i])) {
			// Pop two operands.
			int operand2 = S.top(); S.pop();
			int operand1 = S.top(); S.pop();
			// Perform operation
			int result = PerformOperation(expression[i], operand1, operand2);
			//Push back result of operation on stack.
			S.push(result);
		}
        // @TODO
		else if(IsNumericDigit(expression[i])){
			// Extract the numeric operand from the string
			// Keep incrementing i as long as you are getting a numeric digit.
			int operand = 0;
			while(i<expression.length() && IsNumericDigit(expression[i])) {
				// For a number with more than one digits, as we are scanning from left to right.
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10
				// and add the new digit.
				operand = (operand*10) + (expression[i] - '0');
				i++;
			}
			// Finally, you will come out of while loop with i set to a non-numeric character or end of string
			// decrement i because it will be incremented in increment section of loop once again.
			// We do not want to skip the non-numeric character by incrementing i twice.
			i--;

			// Push operand on stack.
			S.push(operand);
		}
	}
	// If expression is in correct format, Stack will finally have one element. This will be the output.
	return S.top();
}

// Function to verify whether a character is numeric digit.
bool IsNumericDigit(char C)  {
	return (C >= '0' && C <= '9') ? true:false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C) {
	return (C == '+' || C == '-' || C == '*' || C == '/') ? true:false;
}

// Function to perform an operation and return output.
int PerformOperation(char operation, int operand1, int operand2) {
	if(operation == '+') return operand1 + operand2;
	else if(operation == '-') return operand1 - operand2;
	else if(operation == '*') return operand1 * operand2;
	else if(operation == '/') return operand1 / operand2;

	else cout<<"Unexpected Error \n";
	return -1;
}


// https://www.cnblogs.com/grandyang/p/4247718.html
// leetcode 保证 表达式有效
#include <string>
int evalRPN(vector<string>& tokens) {
    if (tokens.size() == 1) return stoi(tokens[0]);
    stack<int> st;
    for (const auto& i : tokens) {
        // operand
        if (i != "+" && i != "-" && i != "*" && i != "/") {
            st.push(stoi(i));
        } else { // operator
            // 注意num的顺序
            int num1 = st.top(); st.pop();
            int num2 = st.top(); st.pop();
            if (i == "+") st.push(num2 + num1);
            if (i == "-") st.push(num2 - num1);
            if (i == "*") st.push(num2 * num1);
            if (i == "/") st.push(num2 / num1);
        }
    }
    return st.top();
}

// @SEE https://leetcode.com/problems/basic-calculator/
// 1. atoi 实现
// 2. stack 进行eval

// https://github.com/john-Ly/calculator/blob/master/parser.h 参照编译原理的方式(生成tocken流)
// 然后对tocken进行pop 进行执行得到一颗抽象语法树  (写麻烦了)