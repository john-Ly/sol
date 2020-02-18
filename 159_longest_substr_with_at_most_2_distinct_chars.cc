#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// 至多两个不同的字符 --> 至多k个不同的字符
// topic: 滑动窗口
// 优先第二种方法

// https://www.cnblogs.com/grandyang/p/5185561.html
// https://www.cnblogs.com/grandyang/p/5351347.html
// https://leetcode.com/problems/minimum-window-substring/discuss/26808/Here-is-a-10-line-template-that-can-solve-most-'substring'-problems

namespace so1 {
int lengthOfLongestSubstringTwoDistinct(string s) {
    int res = 0, left = 0, cnt = 0;
    // unordered_map<char, int> m;
    // hash记录每个字符出现的次数
    vector<char> m(128, 0);

    for (int right=0; right<s.size(); right++) {
        if(m[s[right]]++ == 0) cnt++;

        while (cnt > 2) {  // hash_map记录了所有字符的映射数量
            if (--m[s[left]] == 0) cnt--; // 要删除一个字符出去
            ++left;
        }
        // while退出后, 始终保持 滑动窗口最多只有两个不同的字符
        res = max(res, right-left+1);
    }
    return res;
}
}

// unorderd_map可以用来统计字符出现的个数 或者 下标
// 滑动窗口问题不需要字符已经出现的次数
namespace so2 {
int lengthOfLongestSubstringTwoDistinct(string s) {
    int res = 0, left = 0;
    unordered_map<char, int> m;
    for (int i = 0; i < s.size(); ++i) {
        m[s[i]] = i;
        while (m.size() > 2) {
            // 说明该字符没有重复 滑动左边界 要删除该字符
            if (m[s[left]] == left) m.erase(s[left]);
            ++left;
        }
        res = max(res, i - left + 1);
    }
    return res;
}
}

int main () {
    std::string s{"eceba"};
    cout << "map1: " << so1::lengthOfLongestSubstringTwoDistinct(s) << endl;
    cout << "map2: " << so2::lengthOfLongestSubstringTwoDistinct(s) << endl;

    return 0;
}