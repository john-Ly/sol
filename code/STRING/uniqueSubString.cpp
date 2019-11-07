#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

struct SuffixComparator {
	const string s;
	SuffixComparator(const string& s) : s(s) { }
	bool operator() (int i, int j) {
		// 不用 s.substr() 使用 strcmp() 函数, 能够减少生成临时对象的开销
		return strcmp(s.c_str()+i, s.c_str()+j) < 0;
	}
};

vector<int> getSuffixArrayNaive(const string& s) {
	// 生成保存后缀起始位置的数组
	vector<int> perm;
	for(int i=0; i<s.size(); ++i)
		perm.push_back(i);
	// 利用比较后缀的比较符排序
	std::sort(perm.begin(), perm.end(), SuffixComparator(s));
	// sort() --- O(n logn)
	return perm;
}

// 返回 S[i...]和S[j...] 公共前缀的的最大长度
// time: O(n)
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while(i<s.size() && j<s.size() && s[i]==s[j]) {
		++i; ++j; ++k;
	}
	return k;
}

// 利用后缀数组计算不同的子字符串的个数
// P475 书
// 字符串的所有子串 都是后缀数组每一个前缀的总和(重复现象 是紧密相连)
// time: O(n^2)
int countSubString(const string& s) {
	vector<int> a = getSuffixArrayNaive(s);
	int ret = 0;
	int n = s.size();

	// 长度为 n 的字符串 共有 n个前缀 或者 n个后缀
	for(int i=0; i<n/*n == a.size()*/; ++i) {
		int cp = 0;
		if(i>0)
  			cp = commonPrefix(s, a[i-1], a[i]);
		// a[i]的 n-a[i]个前缀中 共有cp 个重复的前缀)
		ret += (n - a[i] - cp);
	}
	return ret;
}

// 出现次数>k次的重复子串 中 找出最长的长度
// 求所有 A[i] 和 A[i+k-1]的后缀对 的最长共同前缀
//
// 为什么只要i+k-1就可以， 因为共同的前缀是有"短板"来决定
// time: O(n^2)
int longestFrequent(int k, const string& s) {
	vector<int> a = getSuffixArrayNaive(s);
	int ret = 0;
	for(int i=0; i+k <= s.size(); ++i)
		ret = max(ret, commonPrefix(s, a[i], a[i+k-1]));
	return ret;
}
// 感觉像是对后缀数组进行编号后 操作就简便很多

// http://www.ahathinking.com/archives/121.html == 最长重复子串
// 子字符串R 在字符串L 中至少出现两次，则称R 是L 的重复子串
// 最长重复子串(可重叠 因此可以直接使用后缀数组)
// 其实是上一个函数k=2的特殊情况 (还是木桶的最短板子原理===最长公共前缀)
int longestRepeat(const string& s) {
	vector<int> a = getSuffixArrayNaive(s);
	int ret = 0;
    // int maxIndex = 0; // 可以记录最长重复字串的起始位置
	for(int i=0; i+2 <= s.size(); ++i)
		ret = max(ret, commonPrefix(s, a[i], a[i+1]));
	return ret;
}

int main() {
    string s = "banana";
    cout << countSubString(s) << " ";
    cout << longestFrequent(2, s) << " ";
    cout << longestRepeat(s) << " ";

	return 0;
}
