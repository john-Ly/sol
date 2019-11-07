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

*/
#include<iostream>
#include<stack>
#include<string>
using namespace std;

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
