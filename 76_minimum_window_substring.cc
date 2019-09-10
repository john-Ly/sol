#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

// https://leetcode.com/problems/minimum-window-substring/solution/ 详细介绍滑动窗口  @NOTE
// https://www.cnblogs.com/grandyang/p/4340948.html 作者介绍了 基本思路 废话有点多
// https://leetcode.com/problems/minimum-window-substring/discuss/26808/Here-is-a-10-line-template-that-can-solve-most-'substring'-problems
// 上一个链接总结了滑动窗口的模板  可以解决下相关的问题

/*
    Input:	"aa", "aa"
    Expected:	"aa"
*/

// letterCnt可以换成 hash_map<char, int> 因为t中的字符可能是重复的
// t中重复, s中的子串也要包含这个重复的子串(顺序不要求一致)
string minWindow(string s, string t) {
    if (s.empty() || t.empty()) return "";
    vector<int> letterCnt(128, 0); // 键盘可以输入的字符个数+ 记录的窗口中S在t中字符对应重复的个数(该数值为0说明 滑动窗口不满足全部字符包含的条件)
    for (char c : t) ++letterCnt[c];

    int left = 0, cnt = 0, minLeft = 0, minLen = INT_MAX;
    for (int right = 0; right < s.size(); ++right) {
        // 如果letterCnt有记录 减一, 然后更新cnt
        // S: [abaacbab]  t:[abc]
        // letCnt['a'] = -2;
        if (--letterCnt[s[right]] >= 0) ++cnt;  // >=0 说明这是t中的字符, 不相关字符会变为负数

        // 目前滑动窗口包含了t中所有字符, 开始缩小左边界
        while (cnt == t.size()) {
            if (minLen > right - left + 1) {
                minLeft = left;
                minLen = right - left + 1;
            }
            if (++letterCnt[s[left]] > 0) --cnt;  // 窗口不满足所有t的字符(letCnt[c] == 0 说明这个字符还在滑动窗口中)
            ++left; // 缩小左边界
        }
    }

    // minLen = INT_MAX
    if(minLen > s.size()) return "";
    else return s.substr(minLeft, minLen);
}

int main() {
    string s = "abaacbab";
    string t = "abc";

    string s1 = "ADOBECODEBANC";
    string t1 = "ABC";

    auto a = minWindow(s1, t1);
    cout << a << endl;

    return 0;
}