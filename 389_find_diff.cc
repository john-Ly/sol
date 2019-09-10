#include <iostream>
#include <unordered_map>
using namespace std;

// https://www.cnblogs.com/grandyang/p/5816418.html

// 异或来找出只有一个的字符
char findTheDifference(string s, string t) {
    char res = 0;
    for (char c : s) res ^= c;
    for (char c : t) res ^= c;
    return res;
}

// @TODO hash_map的使用 允许重复(直接使用128个字母的数组也可以 因为重复正数)
char findTheDifference(string s, string t) {
    unordered_map<char, int> m;
    for (char c : s) ++m[c];
    for (char c : t) {
        if (--m[c] < 0) return c;
    }
    return 0;
}