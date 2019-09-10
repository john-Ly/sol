#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4385822.html
// https://leetcode.com/problems/group-anagrams/solution/
// 分析(排序 或者 统计字符出现的次数)

//
// 错位词重新排序后都会得到相同的字符串，以此作为key，
// 将所有错位词都保存到字符串数组中，建立key和字符串数组之间的映射，最后再存入结果res中即可
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    unordered_map<string, vector<string>> m;
    for (string str : strs) {
        string t = str;
        sort(t.begin(), t.end());
        m[t].push_back(str);
    }

    for (auto a : m) {
        res.push_back(a.second);
    }

    return res;
}

// 用一个大小为26的int数组来统计每个单词中字符出现的次数，然后将int数组转为一个唯一的字符串，跟字符串数组进行映射，这样我们就不用给字符串排序了
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    unordered_map<string, vector<string>> m;
    for (string str : strs) {
        vector<int> cnt(26, 0); // 题目限定所有字符串全是小写字母
        string t = "";
        for (char c : str) ++cnt[c - 'a'];
    // "abc" ==> "1230...0"
    // "cba" ==> "1230...0" 所以可以作为key
        for (int d : cnt) t += to_string(d);
        m[t].push_back(str);
    }
    for (auto a : m) {
        cout << a.first << endl;
        res.push_back(a.second);
    }
    return res;
}


bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    vector<int> cnt(26, 0); // 题目限定所有字符串全是小写字母

    for (char c : s) ++cnt[c - 'a'];
    for (char c : t) {
        --cnt[c - 'a'];
        if(cnt[c - 'a'] < 0) return false;
    }
    return true;
}