// http://www.ahathinking.com/archives/123.html 最长不重复子串

// @NOTE 有时空复杂度的分析
// https://leetcode.com/problems/longest-substring-without-repeating-characters/solution/
// The previous implements all have no assumption on the charset of the string s.
// If the charset is rather small, replace the Map with an integer array as direct access table.

// Commonly used tables are:
// int[26] for Letters 'a' - 'z' or 'A' - 'Z'
// int[128] for ASCII
// int[256] for Extended ASCII

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

// Brute Force
// time O(n^3) = n^2 * n
// space O(min(n, m))  unordered_set需要的空间大小
namespace so1 {
    // 左闭右开 time: O(n)
    bool allUnique(string s, int start, int end) {
        unordered_set<char> hash;
        for (int i = start; i < end; i++) {
            if (hash.count(s[i])) return false;
            hash.insert(s[i]);
        }
        return true;
    }

    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j <= n; j++)
                // 左闭右开 计算长度 j-i即可; 左闭右闭 计算长度 j-i+1
                if (allUnique(s, i, j)) ans = max(ans, j - i);
        return ans;
    }
}

// sliding window + hash_map
namespace so2 {
/*
http://www.cnblogs.com/grandyang/p/4480780.html

如果当前遍历到的字符从未出现过，那么直接扩大右边界
如果之前出现过，那么就分两种情况，在或不在滑动窗口内
  0. 如果不在滑动窗口内，那么就没事，当前字符可以加进来
  1. 如果在的话，就需要先在滑动窗口内去掉这个已经出现过的字符了，去掉的方法并不需要将左边界left一位一位向右遍历查找，由于HashMap已经保存了该重复字符最后出现的位置，所以直接移动left指针就可以了。
 */

// so2 和 so4思路相同不过 做边界使用了i=-1 更直接(左开右闭)
int lengthOfLongestSubstring(string s) {
    int res=0, left=-1, n=s.size();
    // 由于窗口在不停向右滑动，所以我们只关心每个字符最后出现的位置，并建立映射
    // map通过记录重复字符 *最后一次出现的位置* 可以直接跳转  因此优于unorderd_set
	// unordered_map<int, int> dic;
	vector<int> dic(256, -1);  // 键盘只能表示128个字符 (当前字符 对应的下标 char --> index)

	for (int right=0; right<n; right++) {
        // 当前字符之前出现过 + 在滑动窗口内 (滑动窗口左边界收缩)
        // if(dic.count(s[i]) && dic[s[i]] > i) i = dic[s[i]];
        if(dic[s[right]] > left) left = dic[s[right]];

        dic[s[right]] = right;
        res = std::max(res, right-left);
    }
    return res;
}
}

// sliding window + hash_set
namespace so3 {
// The size of the Set is upper bounded by the size of the string n and the size of the charset/alphabet m.
// space : O(min(n, m))
// 双指针做法
int lengthOfLongestSubstring(string s) {
    int res = 0, i = 0, j = 0,/*i, j 滑动窗口的左右边界 左闭右开*/ n = s.size();
    unordered_set<char> t;
    while (i<n && j<n) {
        if (!t.count(s[j])) {
            t.insert(s[j++]);
            // res = max(res, (int)t.size());
            res = max(res, j-i);
        }  else {
        // 会逐个删除 直到遇到重复的为止
        // "abccab"  当遇到'c'时,先删除a, 下一轮在删除b 最后在删除c
        // ****窗口内维护的都是没有重复的字符串 并且 保持连续
            t.erase(s[i++]);
        }
    }
    return res;
}
}

namespace so4 {
/**
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/discuss/1730/Shortest-O(n)-DP-solution-with-explanations
 * Solution (DP, O(n)):
 *
 * Assume L[i] = s[m...i], denotes the longest substring without repeating
 * characters that ends up at s[i], and we keep a hashmap for every
 * characters between m ... i, while storing <character, index> in the
 * hashmap.

 * We know that each character will appear only once.
 * Then to find s[i+1]:
 * 1) if s[i+1] does not appear in hashmap
 *    we can just add s[i+1] to hash map. and L[i+1] = s[m...i+1]
 * 2) if s[i+1] exists in hashmap, and the hashmap value (the index) is k
 *    let m = max(m, k), then L[i+1] = s[m...i+1], we also need to update
 *    entry in hashmap to mark the latest occurency of s[i+1].
 *
 * Since we scan the string for only once, and the 'm' will also move from
 * beginning to end for at most once. Overall complexity is O(n).
 *
 * If characters are all in ASCII, we could use array to mimic hashmap.
 */

int lengthOfLongestSubstring(string s) {
    // for ASCII char sequence, use this as a hashmap
    vector<int> charIndex(256, -1);
    int longest = 0, m = 0;

    for (int i = 0; i < s.length(); i++) {
        m = max(charIndex[s[i]] + 1, m);    // automatically takes care of -1 case
        charIndex[s[i]] = i;
        longest = max(longest, i - m + 1);
    }

    return longest;
}
}

int main () {
    std::string s{"ABDEFGABEF"};
    cout << "brute-force: " << so1::lengthOfLongestSubstring(s) << endl;
    cout << "slide-set: " << so3::lengthOfLongestSubstring(s) << endl;
    cout << "slide-map: " << so2::lengthOfLongestSubstring(s) << endl;

    return 0;
}