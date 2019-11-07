#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 经过多少次循环位移(circular shift) 才能找到其他字符串
// 联想到图论 ac自动机

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

vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;

	// pi[i]= 既是 N[...i]的前缀又是后缀的字符串的最大长度
	vector<int> pi = getPartialMatch(N);
	// 从 begin =matched =0 开始
	int begin = 0, matched = 0;
	while(begin <= n - m) {
		if(matched < m && H[begin + matched] == N[matched]) {
			++matched;
			// 最终, m 个字符都相互匹配, 则添加到答案目录
			if(matched == m) ret.push_back(begin);
		} else {
			// 异常: matched 等于0时, 从下一个位置开始继续比较
			if(matched == 0)
				++begin;
			else {
				begin += matched - pi[matched-1];
				// 即使移动了 begin 也不必重新开始比较
				// 即使移动了, pi[matched-1]个字符总是一致
				matched = pi[matched-1];
			}
		}
	}
	return ret;
}

int shifts(const string& original, const string& target) {
	return kmpSearch(original+original, target)[0];
}

int main() {
    string original = "aabaa";
    string target = "aaaba";
   	cout << shifts(original, target) << " ";

	return 0;
}
