#include <iostream>
#include <cstring> // memset()
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

// http://www.ahathinking.com/archives/115.html
// 最长公共子序列(不要求连续)
// https://blog.csdn.net/lisonglisonglisong/article/details/41596309
// 上述博客比较完整的解释


string X = "ABCBDAB";
string Y = "BDCABA";
set<string> setOfLCS;

// O(2^n)
// lcs_native(m, n) = 返回当两个字符串长度分别为 m, n时，公共子序列最大的长度

// dp[i][j] = 0  如果i=0或j=0
// dp[i][j] = dp[i-1][j-1] + 1  如果X[i-1] = Y[i-1]
// dp[i][j] = max{ dp[i-1][j], dp[i][j-1] }  如果X[i-1] != Y[i-1]
int lcs_naive(int m, int n) {
	if (m == 0 || n == 0)    // case-1: size == 0
		return 0;
	if (X[m-1] == Y[n-1])
		return lcs_naive(m-1, n-1) + 1;
	else
		return max(lcs_naive(m, n-1), lcs_naive(m-1, n));
}

// 有点类似 三角形最大和 不需要for循环 状态方程的转移可以利用递归 进入最底层
// O(mn)
int cache[11][11];
int mark[11][11];
int lcs_dp(int m, int n) {
	int& ret = cache[m][n];
	if (m == 0 || n == 0)
		return ret = 0;

	if(ret != -1) return ret;

	if (X[m-1] == Y[n-1]) {
		ret = lcs_dp(m-1, n-1) + 1;
		mark[m][n] = 1;
	} else if (cache[m][n-1] >= cache[m-1][n]) {
		ret = lcs_dp(m, n-1);
		mark[m][n] = 2;
	} else if (cache[m][n-1] < cache[m-1][n]) {
		ret = lcs_dp(m-1, n);
		mark[m][n] = 3;
	}

	return ret;
}

// only print one lcs_string
// version-2:
// @TODO 如何遍历所有的空间 求出所有可能的结果
void printLcs(int m, int n) {
	if(m == 0 || n == 0) return;

	if (mark[m][n] == 1) {
		printLcs(m-1, n-1);
		cout << X[m-1];
	}
    else if (mark[m][n] == 2) printLcs(m, n-1);
	else if (mark[m][n] == 3) printLcs(m-1, n);
	else return;
}

int main() {
	memset(cache, -1, sizeof(cache));
	memset(mark, -1, sizeof(mark));

	cout << "The length of LCS is " << lcs_naive(X.size(), Y.size()) << endl;
	cout << "The length of LCS is " << lcs_dp(X.size(), Y.size()) << endl;

	printLcs(X.size(), Y.size());

	return 0;
}
