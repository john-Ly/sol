#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// https://leetcode.com/problems/length-of-last-word/discuss/21892/7-lines-4ms-C%2B%2B-Solution
int lengthOfLastWord(const string& s) {
    int len = 0, tail = s.length() - 1;
    while (tail >= 0 && s[tail] == ' ') tail--;
    while (tail >= 0 && s[tail] != ' ') {
        len++;
        tail--;
    }
    return len;
}

int lengthOfLastWord2(string s) {
    string word("");
    stringstream ss(s);
    // stream有点类似队列, 循环处理完, 应该只保留最后一个
    while (ss >> word){}
    return word.size();
}

//@TODO 可以使用stream get_line来进行操作

int main() {
    string s = "Hello world";
    cout << lengthOfLastWord(s) << endl;
    cout << lengthOfLastWord2(s) << endl;

    return 0;
}