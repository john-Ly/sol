#include <iostream>
#include <cstring> // memset()
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

// 使用后缀数组 将最长回文子串问题 改为 最长公共前缀
namespace so3 {
// 这种做法忽略了一种情况 字符串本身 存在回文子序列

struct SuffixComparator {
	const string s;
	SuffixComparator(const string& s) : s(s) { }
	bool operator() (int i, int j) {
		return strcmp(s.c_str()+i, s.c_str()+j) < 0;
	}
};

vector<int> getSuffixArrayNaive(const string& s) {
	vector<int> perm;
	for(int i=0; i<s.size(); ++i)
		perm.push_back(i);
	std::sort(perm.begin(), perm.end(), SuffixComparator(s));
	return perm;
}

// 最长公共子串: 要保证找到公共子串后二者只有一个#号，这样才表示来自不同的字符串 (可能s1本身有重复字符串)
// O(3n)
int commonPrefix(const string& s, int i, int j) {
    int k = 0;
    int cnt = 0;
    auto s1 = s.substr(i);
    if ( s1.find("#") != std::string::npos) cnt++;
    auto s2 = s.substr(j);
    if ( s2.find("#") != std::string::npos) cnt++;

    if(cnt == 1) {
        while(i<s.size() && j<s.size() && s[i]==s[j]) {
            ++i; ++j; ++k;
        }
    }
	return k;
}

// 如果某一个子串s是它们的公共子串，则s一定会在连接后字符串后缀数组中出现两次，这样就将最长公共子串转成最长重复子串的问题了
string longestPalindrome(string s1) {
    auto s2 = s1;
    std::reverse(s2.begin(), s2.end());
    auto s = s1 + "#" + s2;
	vector<int> a = getSuffixArrayNaive(s);
    for (auto i: a) cout << i << " ";
    cout << endl;
    int candId = -1, maxLen = 0;
	for(int i=0; i+2 <= s.size(); ++i) {
        auto local = commonPrefix(s, a[i], a[i+1]);
        if(maxLen < local) {
            maxLen = local;
            candId = a[i];
        }
    }

    if(candId == -1) return "";
    else return s.substr(candId, maxLen);
}

}

namespace so1 {
// https://www.cnblogs.com/grandyang/p/4464476.html
    // 博主的实现比较简单
class Solution {
  private:
  int start, cnt;
public:
    string longestPalindrome(string s) {
      if (s.size() < 2) return s;
      int n = s.size();
      start = 0, cnt = 0;

      // 循环的边界条件比较关键
      for (int i = 0; i < n - 1; ++i) {
          expandAroundCenter(s, i, i);
          expandAroundCenter(s, i, i + 1);
      }
      return s.substr(start, cnt);
    }

    // 回文可以从字符串中心进行两边扩散 对称相等即可
    // 函数返回符合回文要求的字符长度
    //  bab
    //  expand(s, 1, 1) => 3
    //  expand(s, 1, 2) => 0  ab之间的回文串就是空串
    void expandAroundCenter(string& s, int L, int R) {
        while (L >= 0 && R < s.size() && s[L] == s[R]) {
            --L; ++R;
        }
        // 循环退出 左开(回文串或者空串)右开
        auto len = R - L - 1;
        if (len > cnt) {
        start = L + 1;
        cnt = len;
        }
    }
};
}

namespace so_dp {
// https://www.cnblogs.com/grandyang/p/7404777.html
// 647 找出字符串中包含回文字符串的个数
int countSubstrings(string s) {
    int n = s.size(), dp[n][n] = {0}, res = 0;
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
        for (int j = 0; j <= i; ++j) {
            dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
            if (dp[j][i]) ++res;
        }
    }
    return res;
}

// 左闭右闭
// 表示字符串区间[i, j] 是否是回文字符串
// 天然递归 的思考
// dp(i, j) = dp(i+1, j-1) && Si == Sj
//
// dp(i, j) == 1,                          if i==j
//          == s[i]==s[j]                  if j==i+1
//          == s[i]==s[j] && dp[i+1][j-1]  if j>i+1

// "ab"  结果是 "a"
// len = 1 初始化
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() < 2) return s;
        int n = s.size(), dp[n][n] = {0}, left = 0, len = 1;
        // 因为是从左往右 遍历所以i, j有点反直觉
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            for (int j = 0; j < i; ++j) {
                dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
                if (dp[j][i] && len < i - j + 1) {
                    len = i - j + 1;
                    left = j;
                }
            }
        }
        return s.substr(left, len);
    }
};
}

int main() {
    {
        using namespace so1;
        auto s = "babad";
        auto s1 = "aacdefcaa";  // 正确: aa  输出: aac (后缀数组出错)
        cout << longestPalindrome(s) << endl;
    }

	return 0;
}