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


int main() {
    {
        using namespace so3;
        auto s = "babad";
        auto s1 = "aacdefcaa";  // 正确: aa  输出: aac (后缀数组出错)
        cout << "lps_suffix: " << longestPalindrome(s1) << endl;
    }

	return 0;
}

