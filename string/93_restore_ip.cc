#include <string>  // 新增加了转换为  int的正数
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4305572.html
// 1. 只要遇到字符串的子序列或配准问题首先考虑动态规划DP
// 2. 只要遇到需要求出所有可能情况首先考虑用递归。 (暴搜)
// https://www.cnblogs.com/grandyang/p/6185339.html

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

// ip地址转换为4字节无符号整数
unsigned int ipstr_ipint(string ip) {
    unsigned int x = 0;
    stringstream ss(ip);
    string t;
    while (getline(ss, t, '.')) {
        x = x*256 + stoi(t);
    }
    return x;
}

string validIPAddress(string IP) {
    stringstream is(IP);
    string t = "";
    int cnt = 0;
    if (IP.find(':') == string::npos) { // Check IPv4
        // 换行符可以自己定义成 "."
        for(string t; getline(is, t, '.'); cnt++) {
            if (cnt > 4 || t.empty() || (t.size() > 1 && t[0] == '0') || t.size() > 3) return "Neither";
            for (char c : t) {
                if (c < '0' || c > '9') return "Neither"
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

// 动态规划题目
// "25525511135"  找出所有可能的string类型
// ["255.255.11.135", "255.255.111.35"]
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


// 从IP中找出 对应的省份号码(IP 地址 反映天气)
struct IPrange {
    // 左闭右闭
    uint32_t startIp;
    uint32_t endIp;
    int value;  代表省份的号码

    bool operator<(const IPrange& rhs) const { return startIp < rhs.startIp; }
}

int findIpValue(const vector<IPrange>& ranges, uint32_t ip) {
    int res = -1;
    if (!ranges.empty()) {
        IPrange target {ip, 0, 0};
        auto it = std::lower_bound(ranges.begin(), ranges.end(), target);
        if (it == ranges.end()) --it;
        else if (it != ranges.begin() && it->startIp > ip) --it;

        if (it->startIp <= ip && it->endIp >= ip) {
            res = it->value;
        }
    }
    return res;
}