#include <iostream>
#include <vector>
#include <cstring> // memset()
using namespace std;

const int MOD = 1000000007;

/*
Time Complexity: T(n) = T(n-1) + T(n-2) which is exponential.
We can observe that this implementation does a lot of repeated work (see the following recursion tree).
                         fib(5)
                     /             \
               fib(4)                fib(3)
             /      \                /     \
         fib(3)      fib(2)         fib(2)    fib(1)
        /     \        /    \       /    \
  fib(2)   fib(1)  fib(1) fib(0) fib(1) fib(0)
  /    \
fib(1) fib(0)
Extra Space: O(n) if we consider the function call stack size, otherwise O(1).
*/
int fib_recursion(int n) {
	return n < 2 ? 1 : (fib_recursion(n-1) + fib_recursion(n-2));
}

/*
Dynamic Programming
Time Complexity: O(n)
Extra Space: O(n)

递归+记忆数组
*/
// 给出长方形大小 计算铺设方法的种类 + 给出楼梯台阶数, 计算步数的种类
// https://leetcode.com/problems/climbing-stairs/solution/  详细解释
vector<int> cache(101, -1);
int tiling(int width) {
    // 错误处理 + 初始条件
    if(width == 0) return 0;
	if(width <= 2) return width;
	// 书上的做法 是默认0也是1(虚构)
    // if(width <= 1) return 1;

    // cache
	int& ret = cache[width];
	if(ret != -1) return ret;

	return ret = ( tiling(width-2)+tiling(width-1) ) % MOD;
}

// Time Complexity: O(n)
// Extra Space: O(1)
// 返回第n个 fib数  (假设第0个数是 0 )
// fib: 1, 1, 2, 3, 5...
// @SEE 书P247 迭代动归法(因为需要前面两行信息)
long FibIter ( long n ) {
    // 前提是 已经第一个数是1, 求第二个数(循环1次), 求第三个数(循环3次)
	if ( n <= 1 ) return n;
	long twoback = 0, oneback = 1, Current;
	for ( int i = 2; i <= n; i++ ) { // 循环n-1次
		Current = twoback + oneback;
		twoback = oneback; oneback = Current;
	}
	return Current;
}

// @SEE 书P247 迭代动归法(因为需要前面两行信息)
// 求出第n个fib数的 后五位数
int FibIter ( int n ) {
	if ( n <= 1 ) return n;
    int seq[3];
    seq[0] = 0; seq[1] = 1;
    // 有点向加法器 后面五位
	for ( int i = 2; i <= n; i++ ) { // 循环n-1次
        seq[i%3] = (seq[(i-1)%3] + seq[(i-2)%3]) % 100000;
	}
	return seq[n%3];
}

int Qpow(int a,int n) {
    int ans = 1;
    while(n) {
        if(n&1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

int main() {
	memset(cache, -1, sizeof(cache));
	cout << tiling(5) << endl;

	return 0;
}
