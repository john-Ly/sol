#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

// https://leetcode.com/problems/decode-ways/discuss/30451/Evolve-from-recursion-to-dp
// @TODO
namespace so1 {
// numDecodings(p) = 表示s.substr(0, p) 内可以表示的组合数
//   已经处理的子问题 [0, p-1]  待解决的子问题 [p...] // f(p) = f(p+1) + f(p+2) // 这道题目跟正则表达式很像  @TODO int numDecodings(int p, string& s) {
    int n = s.size();
    // s[p] == '0' 表示
    if(p == n) return 1;
    if(s[p] == '0') return 0;

    int res = numDecodings(p+1,s);
    if( p < n-1 && (s[p]=='1'|| (s[p]=='2'&& s[p+1]<'7')))
       res += numDecodings(p+2,s);
    return res;
}

int numDecodings(string s) {
    return s.empty() ? 0: numDecodings(0,s);
}
}


namespace so2 {
int numDecodings(int p, string& s, vector<int>& v) {
    int n = s.size();
    // s[p] == '0' 表示

    if(p == n) return 1;
    int& res = v[p];
    if(s[p] == '0') return 0;

    res = numDecodings(p+1,s,v);
    if( p < n-1 && (s[p]=='1'|| (s[p]=='2'&& s[p+1]<'7')))
        res += numDecodings(p+2,s,v);
    return res;
}

int numDecodings(string s) {
    vector<int> cache(s.size(), -1);
    return s.empty() ? 0: numDecodings(0,s,cache);
}
}

namespace so3 {
int numDecodings(string s) {
    int n = s.size();
    vector<int> dp(n+1);
    dp[n] = 1;
    for(int i=n-1;i>=0;i--) {
        if(s[i]=='0') dp[i]=0;
        else {
            dp[i] = dp[i+1];
            if(i<n-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) dp[i]+=dp[i+2];
        }
    }
    return s.empty()? 0 : dp[0];
}
}

namespace so4 {
int numDecodings(string s) {
    int p = 1, pp, n = s.size();
    for(int i=n-1;i>=0;i--) {
        int cur = s[i]=='0' ? 0 : p;
        if(i<n-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) cur+=pp;
        pp = p;
        p = cur;
    }
    return s.empty()? 0 : p;
}
}


namespace bottom_up {
// https://www.cnblogs.com/grandyang/p/4313384.html
int numDecodings(string s) {
    if (s.empty() || s[0] == '0') return 0;
    vector<int> dp(s.size()+1, 0);  // 如果字符全是0 初始为1不合适
    dp[0] = 1;  // 针对i=1的情况
    for(int i=1; i<=s.size(); ++i) {
        // 每个字符 先用一个字符进行判断
        dp[i] = (s[i-1] == '0') ? 0 : dp[i-1];
        if (i>1 && (s[i-2]=='1'|| (s[i-2]=='2' && s[i-1]<'7'))) {
            dp[i] += dp[i-2];
        }
    }
    return dp.back();
}
}

int main() {
    {
        using namespace so1;
        string s = "111022";
        cout << numDecodings(s) << endl;
    }

    {
        using namespace so2;
        string s = "1022";
        cout << numDecodings(s) << endl;
    }

    return 0;
}