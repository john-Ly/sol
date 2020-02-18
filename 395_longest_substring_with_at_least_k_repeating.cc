#include <string>
#include <iostream>

using namespace std;
// https://www.cnblogs.com/grandyang/p/5852352.html

// 最长子串: 每个字符都至少重复k 次
// topic: 滑动窗口 + hash 字符串特化 + 二进制运算
//  最笨的方法 但是@TODO 不理解

namespace so1 {
// 子串: 连续 (子序列 不连续)
int longestSubstring(string s, int k) {
    int res = 0, i = 0, n = s.size();
    // 外层循环 针对每一个可能的字符起始位置 [0, n-k]
    while (i + k <= n) {
        int m[26] = {0}, mask = 0, max_idx = i;

        // 从 [i:] 最后所有的字符串范围内
        for (int j = i; j < n; ++j) {
            int t = s[j] - 'a';
            ++m[t];

            // |= 添加元素  &= (~(1<<t)) 删除元素
            if (m[t] < k) mask |= (1 << t);
            else mask &= (~(1 << t));
            // 如果 mask为0, i-j内的字符串符合题目要求
            // (某个字符个数满足条件 则将该位置0)
            if (mask == 0) {
                res = max(res, j - i + 1);
                max_idx = j;
            }
        }
        i = max_idx + 1;
    }
    return res;
}

}