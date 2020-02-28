#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/longest-valid-parentheses/solution/
// 给出的解法很多  很有启发

// stack比较直观
int longestValidParentheses(string s) {
    // start变量来记录合法括号串的起始位置
    int res = 0, start = 0;
    stack<int> m;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') m.push(i);
        else if (s[i] == ')') {
            // m为空 说明当前遇到的字符串是非法的, 记录下一个坐标
            if (m.empty()) start = i + 1;
            else {
                m.pop();
                res = m.empty() ? max(res, i - start + 1) : max(res, i - m.top());
            }
        }
    } // for()
    return res;
}


// 动态规划的问题不太理解 @TODO

// 前后扫描  比较朴素
// 限定字符串里面只包含 "("  ")"
int longestValidParentheses2(string s) {
    int left = 0, right = 0, maxlength = 0;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') left++;
        else right++;

        if (left == right) {
            maxlength = max(maxlength, 2 * right);
        } else if (right >= left) {
            left = right = 0;
        }
    }

    left = right = 0;
    for (int i = n-1; i >= 0; i--) {
        if (s[i] == '(') left++;
        else right++;

        if (left == right) {
            maxlength = max(maxlength, 2 * left);
        } else if (left >= right) {
            left = right = 0;
        }
    }
    return maxlength;
}

int main() {
    auto tmp = longestValidParentheses2("()(((()))");
    cout << tmp << endl;

    return 0;
}
