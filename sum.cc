#include <iostream>
using namespace std;

// O(n)
int sum(int n) {
	int ret = 0;
	for(int i=1; i<=n; i++)
	    ret += i;
	return ret;
}

// 递归和分治的区别: 递归将问题分解为1个小问题和剩余的问题
// T(n) = T(n-1) + O(1)
// O(n)
int recursiveSum(int n) {
	if(n == 1) return 1;

	return n + recursiveSum(n-1);
}

// divide & conquer : 分治则把问题分解为 同等大小的子问题
// fastSum(n) = 2*fastSum(n/2) + n^2/4

// ref: ada P28 + aqps P122
// O(lg n) -- n(binary)
int fastSum(int n) {
    // 初始条件
	if(n == 1) return 1;
    // n是奇数  容易求偶数的情况
	if(n%2 == 1) return fastSum(n-1) + n;

	return 2*fastSum(n/2) + (n/2)*(n/2);
}

int main() {

    return 0;
}
