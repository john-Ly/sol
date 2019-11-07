#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	// 利用 KMP 找出自己本身 
	// 从 N 中找出 N   begin=0时会找到自己本身, 所以begin不能等于 0
	int begin = 1, matched = 0;
	// 需要比较的字符到达 N 的最后一个位置前一直检索, 并记录所有匹配 
	while(begin + matched < m) {
		if(N[begin + matched] == N[matched]) {
			++matched;
			pi[begin+matched-1] = matched;
		} else {
			// 异常: matched 等于0时, 从下一个位置开始继续比较
			if(matched == 0)
				++begin;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}

// 利用 KMP 的变形 
// 返回既是 S 前缀又是 S` 后缀的字符串的最大长度
// maxOverlap S <--reverse--> S'  
int maxOverlap(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	
	// 从 begin =matched =0 开始
	int begin = 0, matched = 0;
	// 尝试 0 到 |S|-1 之间的所有位置 
	while(begin < n) {
		if(matched < m && a[begin + matched] == b[matched]) {
			++matched;
			// 找出第一个 
			if(begin+matched == n)
				return matched;
		} else {
			if(matched == 0)
				++begin;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return 0;
}

int main() {
    string haystack = "anon";
    // std::reverse(std::begin(s), std::end(s));
    string needle = "nona";
    cout << maxOverlap(haystack, needle) << " ";

	return 0;
}
