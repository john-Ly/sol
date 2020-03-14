#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4452220.html
// @SEE dp/combination_sum.cc

static const vector<string> dict{"", "", "abc",
                                "def", "ghi", "jkl",
                                "mno", "pqrs", "tuv",
                                "wxyz"};

// 思路很想求组合  迭代思路很直接 但是如果迭代很多 ==> 考虑递归
vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    vector<string> res{""};
    for (auto di : digits) { // 1.找出每个数字代表的字符串

        vector<string> t;  // 临时变量 先存所有的可能组合
        string str = dict[di - '0'];

        for (auto c : str) { // 2. 针对每个字符 2 - [a. b. c]
            for (string s : res) {  // 3. 现有res所有的字符都要后缀加上
                t.push_back(s + c);
            }
        }
        res = t;           // 复制回原数组

    }
    return res;
}

// level: 记录当前生成的字符串的字符个数
// 为什么递归需要 先push 然后pop
// "23"
// 2 - abc    3 - def
// c(3, 1) + c(3,1)       跟之前的combination问题不同
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
