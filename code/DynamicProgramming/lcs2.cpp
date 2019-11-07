#include <iostream>
#include <cstring> // memset()
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

// http://www.ahathinking.com/archives/122.html
// 最长公共子串

// http://blog.iderzheng.com/longest-common-substring-problem-optimization/
// 优化分析

// http://haiyangxu.github.io/posts/2014/2014-07-02-longest_substr_or_subsequence.html

string X = "YXXXXXY"; // 7
string Y = "YXYXXYYYYXXYYYYXYYXXYYXXYXYYYYYYXYXYYXYXYYYXXXXXX"; // 49

namespace so1 {

// 返回 S1[i...]和S2[j...] 公共前缀的的最大长度
// time: O(n)
int commonPrefix(const string& s1, const string& s2, int i, int j) {
	int k = 0;
	while(i<s1.size() && j<s2.size() && s1[i]==s2[j]) {
		++i; ++j; ++k;
	}
	return k;
}
// O(n^3)
int lcs_brute(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    if (m == 0 || n == 0) return 0;

    int maxLen = 0;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            int len = commonPrefix(X, Y, i, j);
            maxLen = max(len, maxLen);
        }
    }
    return maxLen;
}
}

namespace so2 {
// https://blog.csdn.net/qq_25800311/article/details/81607168
// 矩阵的图示 比较直观

// O(n^2)
string getLCS(const string& str1, const string& str2) {
    vector<vector<int> > record(str1.length(), vector<int>(str2.length()));
    int maxLen = 0, maxEnd = 0;
    for(int i=0; i<static_cast<int>(str1.length()); ++i)
        for (int j = 0; j < static_cast<int>(str2.length()); ++j) {
            if (str1[i] == str2[j]) {
                if (i == 0 || j == 0) {
                    record[i][j] = 1;
                }
                else {
                    record[i][j] = record[i - 1][j - 1] + 1;
                }
            }
            else {
                record[i][j] = 0;
            }

            if (record[i][j] > maxLen) {
                maxLen = record[i][j];
                maxEnd = i; //若记录i,则最后获取LCS时是取str1的子串
            }
        }
    return str1.substr(maxEnd - maxLen + 1, maxLen);
}

// int cache[50][50];
// int lcs_dp(int m, int n) {
// 	int& ret = cache[m][n];
// 	if (m == 0 || n == 0)
// 		return ret = 0;

// 	if(ret != -1) return ret;

// 	if (X[m-1] == Y[n-1]) {
// 		ret = lcs_dp(m-1, n-1) + 1;
// 	} else {
// 		ret = 0;
// 	}

// 	return ret;
// }
}

namespace so3 {
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
int lcs_suffix_array(const string& s1, const string& s2) {
    auto s = s2 + "#" + s1;
    cout << s << endl;
	vector<int> a = getSuffixArrayNaive(s);
	int ret = 0;
	for(int i=0; i+2 <= s.size(); ++i)
		ret = max(ret, commonPrefix(s, a[i], a[i+1]));

	return ret;
}
}

int main() {
	cout << "lcs(substring): " << so1::lcs_brute(X, Y) << endl;

    {
        using namespace so2;
        // memset(cache, -1, sizeof(cache));
        string s1 = "abcbced", s2 = "acbcbcef";
        cout << "lcs(substring): " << getLCS(s1, s2) << endl;
    }

    {
        using namespace so3;
        string s1 = "abcbced", s2 = "acbcbcef";
        cout << "lcs(substring): " << lcs_suffix_array(s1, s2) << endl;
    }

	return 0;
}
