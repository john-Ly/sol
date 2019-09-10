#include <string>  // 新增加了转换为  int的正数
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4305572.html
// 1. 只要遇到字符串的子序列或配准问题首先考虑动态规划DP
// 2. 只要遇到需要求出所有可能情况首先考虑用递归。 (暴搜)

// https://www.cnblogs.com/grandyang/p/6185339.html

// @TODO 可以利用递归来做  暂时放下
bool is_valid_recursive(string s, int rest) {
    // 分成4个子问题 然后每一个子问题的结果在组合起来( true && true && true && true )
}

/*
IPv4:
- Should be exactly 4 parts splitted by '.', and the last char cannot be '.'
- The length of each part cannot be larger than 3, and if length is larger than 2, the first digit cannot be 0
- Each part can only be digit, and the value should between 0 and 255

IPv6:
- Should be exactly 8 parts splitted by ':', and the last char cannot be ':'
- The length of each part cannot be larger than 4
- Each part can only be digit, or letter 'a'-'f', 'A'-'F'


https://leetcode.com/problems/validate-ip-address/discuss/95552/My-Straightforward-C%2B%2B-Solution
*/

// @TODO string有一些常用的函数需要查表
// string:   find() + find_if()
// getline(stream, str, del)
string validIPAddress(string IP) {
    istringstream is(IP);
    string t = "";
    int cnt = 0;
    if (IP.find(':') == string::npos) { // Check IPv4
        // 换行符可以自己定义成 "."
        for(string t; getline(is, t, '.'); cnt++) {
            if (cnt > 4 || t.empty() || (t.size() > 1 && t[0] == '0') || t.size() > 3) return "Neither";
            for (char c : t) {
                if (c < '0' || c > '9') return "Neither";
            }
            int val = stoi(t);
            if (val < 0 || val > 255) return "Neither";
        }
        return (cnt == 4 && IP.back() != '.') ? "IPv4" : "Neither";
    } else { // Check IPv6
        // while (getline(is, t, ':')) {
        for(string t; getline(is, t, ':'); cnt++) {
            if (cnt > 8 || t.empty() || t.size() > 4) return "Neither";
            for (char c : t) {
                if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F')) return "Neither";
            }
        }
        return (cnt == 8 && IP.back() != ':') ? "IPv6" : "Neither";
    }
}


vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    restore(s, 4, "", res);
    return res;
}

// k 表示还需要处理几个子问题(分成了4个子问题)
void restore(string s, int k, string out, vector<string> &res) {
    if (k == 0) {
        if (s.empty()) res.push_back(out);
    } else {
        // 因为IPv4字段 0-255 位数只有三种可能
        for (int i = 1; i <= 3; ++i) { // i代表字符串可能的位数
            // 因为substr [0, i) 所以s至少要有i个字符
            if (s.size() >= i && isValid(s.substr(0, i))) {
                // s.substr(i) 表示前面i个字符串已经判断为正确的ip字段
                string optional = (k==1) ? "" : ".";
                restore(s.substr(i), k - 1, out + s.substr(0, i) + optional, res);
            }
        }
    }
}

bool isValid(string s) {
    if (s.empty() || s.size() > 3 || (s.size() > 1 && s[0] == '0')) return false;
    int res = stoi(s);
    return res <= 255 && res >= 0;
}