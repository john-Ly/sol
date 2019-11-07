#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>  // max
#include <cstring> // memset()
using namespace std;

// @TODO 如何生成第k个 fib数

namespace bf {
// s: 已生成的信号
// n: 还需要 "-" 的个数
// m: 还需要 "o" 的个数
void generate(int n, int m, string s) {
	// 初始部分 n=m=0
	if(n==0 && m==0) {
		cout << s << endl; return;
	}

	// 两段代码的次序决定是否按照字典排序
	if(n>0) generate(n-1, m, s+'-');
	if(m>0) generate(n, m-1, s+'o');
}
}

namespace skip {
// 跳过 k-1 个信号后输出第一个信号, 即第k个信号  === 不过还是生成了前面的k-1个信号
int skip = 4-1;
void generate(int n, int m, string s) {
	// 初始部分 skip < 0
	if(skip<0) return;
	// 初始部分 n=m=0
	if(n==0 && m==0) {
		if(skip == 0)
		    cout << s << endl;
		--skip;
		return;
	}

	// 两段代码的次序决定是否按照字典排序
	if(n>0) generate2(n-1, m, s+'-');
	if(m>0) generate2(n, m-1, s+'o');
}
}

namespace skip_bio {
// @TODO
// 将n个- 和 m个. 连到s后面, 用二项式系数表示组合个数  C[n+m][n]
// 跳过 k-1 个信号后输出第一个信号 --- 动态规划
// k 的最大值 +100 防止溢出 只对小于 100 的情况求解
const int M = 1000000000 + 100;
int bino[201][201];
void calcBino() {
	std::memset(bino, 0, sizeof(bino));
	for(int i=0; i<=200; ++i) {
		bino[i][0] = bino[i][i] = 1;  // Cn-0 = 1 = Cn-n
		for(int j=1; j<=i; ++j)
			bino[i][j] = std::min(M, bino[i-1][j-1] + bino[i-1][j]);
	}
}

// time: O(n+m)
void generate(int n, int m, string s) {
	// 初始部分 skip < 0
	if(skip<0) return;
	// 初始部分 n=m=0
	if(n==0 && m==0) {
		if(skip == 0)
		    cout << s << endl;
		--skip;
		return;
	}

    // skip就是应该跳过的数(k-1)
	if(bino[n+m][n] <= skip) {
		skip -= bino[n+m][n]; return;
	}

	// 两段代码的次序决定是否按照字典排序
	if(n>0) generate3(n-1, m, s+'-');
	if(m>0) generate3(n, m-1, s+'o');
}
}

namespace skip_dp {
// 需要先记录bio
string kth(int n, int m, int ski) {
	// 初始部分 n=m=0  @TODO n==0, 只剩下m个 o
	if(n==0) return string(m, 'o');

	if(ski < bino[n+m-1][n-1])
		return '-' + kth(n-1, m, ski);
	return 'o' + kth(n, m-1, ski-bino[n+m-1][n-1]);
}
}

int main() {
	string tmp;
	int n=2, m=2;
    // bf::generate(n, m, tmp);
    skip::generate(n, m, tmp);
    // skip_bio::calcBino();
    // skip_bio::generate(n, m, tmp);
    /*
	skip = 8-1; // 找到第 4 个
	calcBino();
	generate3(n, m, tmp);
	cout << kth(n, m, 3) << endl;
	// 全局变量(skip)如果直接 传入 结果会出现错误
*/
    return 0;
}
