#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace geek {
int brute_force_match(const string& H, const string& N) {
    int i, j, tem;
    int tlen = H.size(), plen = N.size();
    for(i = 0, j = 0; i <= tlen - plen; i++, j = 0) {
        tem = i;
        while(H[tem] == N[j] & j < plen) {
            tem++;
            j++;
        }
        // matched
        if(j == plen) {
            return i;
        }
    }
    // [p] is not a substring of [t]
    return -1;
}
}

namespace normal {
// start_point : |H|-|N|+1
//  comparison : |N|
// Time Complexity : O(|H|*|N|)
vector<int> naiveSearch(const string& H, const string& N) {
	vector<int> ret;
	// 尝试所有起始位置
    // 最后一位:  n-1 -x +1 = m  (n = H.size, m = N.size)
    // @NOTE 无论座标是否从0起始, 计数都是 j-i+1 (i, j是同一体系的合法下标)
	for(int begin=0; begin+N.size()<=H.size(); ++begin) {
		bool matched = true;
		for(int i=0; i<N.size(); ++i) {
			if(H[begin+i] != N[i]) {
				matched = false;
				break;
			}
		}
		if(matched) ret.push_back(begin);
	}
	return ret;
}
}

/* 实质思路也很简单 类比于原始方法求匹配字符串
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	//
	for(int begin=1; begin<m; ++begin) {
		for(int i=0; i<m; ++i) {
			if(N[begin+i] != N[i])
				break;
			pi[begin+i] = max(pi[begin+i], i+1);
		}
	}
	return pi;
}
*/

// 非常巧妙的方法 利用后缀作为 缝衣针  原字符串的前缀做草堆
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

// "aabaa"
//  aa - 2;  a - 1
// 最大长度的前缀的后缀 就是 最大长度的后缀的后缀  aa 后一个 a
// pip[k-1] --> S[...k-1] 既是小于最大长度的 前缀 & 后缀
vector<int> getPrefixSuffix(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);

	int k = s.size(); // 字符串本身既是前缀 又是后缀
	while(k > 0) {
		// S[... k-1]是正确答案
		ret.push_back(k);
		// 既是 S[... k-1]的前缀又是后缀的字符串也是正确答案
		k = pi[k-1];
	}
	return ret;
}

vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;

	// pi[i]= 既是 N[...i]的前缀又是后缀的字符串的最大长度
	vector<int> pi = getPartialMatch(N);
	// 从 begin =matched =0 开始
	int begin = 0, matched = 0;
	while(begin <= n - m) {
		cout << ">>> initial:" << begin << "-" << matched << endl;
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

        cout << "not matched:" << begin << "-" << matched << endl;
		}
	}
	return ret;
}

vector<int> kmpSearch2(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;

	vector<int> pi = getPartialMatch(N);
	// 当前已匹配的个数
	int matched = 0;

	// 遍历 "草堆" 字符串的所有字符
	for(int i=0; i<n; ++i) {
		cout << ">>> initial:" << i << "-" << matched << endl;
		// 第 matched 个字符和 "草堆" 字符串不匹配,
		// 将当前已匹配字符的个数减少到 Pi[matched-1]
		while(matched > 0 && H[i] != N[matched])
  			matched = pi[matched-1];

		// 字符串匹配时
		if(H[i] == N[matched]) {
			++matched;
			if(matched == m) {
				ret.push_back(i-m+1);  // End - Start + 1 = m ;; m 元素个数
				matched = pi[matched-1];
			}
		}
	}
	return ret;
}

int main() {
    string haystack = "AABAACAADAABAAABAA";
    string needle = "AABA";
    string s = "ababbaba";

    string h = "ababbaabaa";
    string n = "aab";

//    for(auto i : getPrefixSuffix(s) )
//      	cout << i << " ";

    for(auto i : kmpSearch2(h, n) )
      	cout << i << " ";

	return 0;
}
