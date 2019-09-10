#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// 原地翻转字符串
// https://www.techiedelight.com/reverse-string-in-place-cpp/
// https://www.techiedelight.com/reverse-string-cpp/ 
// 里面有提到 利用rbegin() 和 rend() 来进行翻转
// for_each函数 + string 的构造函数
//
//

string reverse4(string const &s) {
    // string rev(s.rbegin(), s.rend());
	string rev;
	for_each(s.crbegin(), s.crend(), [&rev] (char const &c) {
				rev = rev.append(1, c);
			});

	return rev;
}


// Function to reverse a string in-place in C++
void reverse(string &s) {
	int n = s.length();
	for (int i = 0; i < n/2; i++)
		std::swap(s[i], s[n-i-1]);
}


// Function to reverse a string in-place in C++
void reverse2(string &s)
{
	int n = s.length();

	std::string::iterator start = s.begin();
	std::string::iterator end = s.end();

	while (std::distance(start, end) > 0) {
		std::swap(*(start++), *(--end));
	}
}

// main function
int main() {
	std::string s("Reverse a string in C++");

	reverse(s);
	cout << s << endl;
	reverse2(s);
	cout << s << endl;
    std::reverse(s.begin(), s.end());
	cout << s << endl;

	cout << reverse4(s) << endl;

	return 0;
}
