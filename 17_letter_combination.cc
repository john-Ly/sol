#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4452220.html

static const vector<string> dict{"", "", "abc",
                                "def", "ghi", "jkl",
                                "mno", "pqrs", "tuv",
                                "wxyz"};

// 思路很想求组合  迭代思路很直接 但是如果迭代很多 ==> 考虑递归
// "23"
vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    vector<string> res{""};
    for (auto di : digits) { // 1.找出每个数字代表的字符串
        vector<string> t;
        string str = dict[di - '0'];
        for (auto c : str) { // 2. 针对每个字符 2 - [a. b. c]
            for (string s : res) {  // 3. 现有res所有的字符都要后缀加上
                t.push_back(s + c);
            }
        }
        res = t;
    }
    return res;
}

// level: 记录当前生成的字符串的字符个数
// 想象整个解的空间就是一颗树
// 为什么递归需要 先push 然后pop
void letterCombinationsDFS(string& digits, int level, string out, vector<string>& res) {
    if (level == digits.size()) {res.push_back(out); return;}
    string str = dict[digits[level] - '0'];
    for (auto c : str) {
        letterCombinationsDFS(digits, level + 1, out+c, res);
    }
}


vector<string> letterCombinations2(string digits) {
    if (digits.empty()) return {};
    vector<string> res;
    letterCombinationsDFS(digits, 0, "", res);
    return res;
}

int main() {
    for(auto& str: letterCombinations("23"))
        cout << str << endl;

    return 0;
}
