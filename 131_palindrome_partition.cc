#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4271456.html
// @SEE 5.longest_ps   动归的思路完全一样
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> out;

        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
            }
        }

        helper(s, 0, out, dp, res);
        return res;
    }

    // 因为out要复用 所以要pop_back()
    // start 指定字符串起始位置
    void helper(string s, int start, vector<string>& out,
                vector<vector<int>>& dp, vector<vector<string>>& res) {
        if (start == s.size()) { res.push_back(out); return; }
        for (int i = start; i < s.size(); ++i) {
            if (!dp[start][i]) continue;
            out.push_back(s.substr(start, i - start + 1));
            helper(s, i + 1, out, dp, res);
            out.pop_back();
        }
    }

    // 左闭右闭
    bool isPalindrome(string s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) return false;
            ++start; --end;
        }
        return true;
    }
};

namespace so2 {
// 当s可以分为多个子回文字符串 求最小的切割数
// "aab"
// "a" + "a" + "b"
// "aa" + "b"  =>   1次
//
// cut[i] = 前i 个字符可以切割成回文字符 最小的切割数
// cut[i] = cut[j-1] + 1  当dp(j, i) 是回文串时
// dp(i, j) = 左闭右闭 (i, j) 范围内 是否是回文串
int partition(string s) {
    int n = s.size();
    if (!n) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<int> cut(n, 0);
    for (int i = 0; i < n; ++i) {
        cut[i] = i; // n个字符最多可以分 n-1次, 即每个单独的字符作为结果
        for (int j = 0; j <= i; ++j) {
            dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
            if (dp[j][i]) {
                //    j==0, [0,i]都是回文 没有分割 ;因为采用的是左闭右闭
                cut[i] = (j == 0) ? 0 : min(cut[i], cut[j-1] + 1);
            }
        }
    }

    return cut[n-1];
}
}



int main() {
    string s = "abcd";
    string s1 = "aacd";
    Solution sol;
    for (auto& v : sol.partition(s1)) {
        for (auto& i : v) cout << i << ", ";
        cout << '\n';
    }
    return 0;
}