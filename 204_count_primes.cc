#include <iostream>
#include <vector>
#include <cstring>   // memset()
#include <cmath>    // sqrt()
using namespace std;


/*
1. 素数(质数) + 素因子分解
   每个合数都可以写成几个质数相乘的形式 分解质因数 分解质因数只针对合数。
2. 埃拉托斯特尼筛法
*/

// 常规解法 很好
bool isprime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    // 除 2 以外的所有偶数 都不是素数
	if (n % 2 == 0) return false;
    int sqrtn = int(sqrt(n));
    for (int i=3; i<=sqrtn; i += 2) {
        if (n%i == 0)
            return false;
    }
    return true;
}

vector<int> factorSimple(int n) {
    vector<int> ret;
    int sqrtn = int(sqrt(n));
    for (int i=3; i<=sqrtn; i += 2) {
        while(n % i == 0) {
            n /= i;
            ret.push_back(i);
        }
    }
    // 2也是素数 所以要考虑这种情况
    if(n>1) ret.push_back(n);
    return ret;
}

#define TM 10000000

bool isPrime[TM+1];  // 函数终止以后 确定isPrime[i]=i 是否是素数
void primeTable(int n) {
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
	int sqrtn = (int)(sqrt(n));

	for (int i=2; i<=sqrtn; i++) {
		if(isPrime[i]) {
            // 对于i的倍数j 设置为isPrime[j]=false
            // 小于i*i的倍数已经删除 不再考虑
			for (long long j=i*i; j<=n; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

// minFactor[i] = i 的最小素数因子
// 28 = 2 x 2 x 7  minFactor[28] = 2
// minFactor[7] = 7 i为素数 为其本身
int minFactor[TM+1];
void minFactorTable(int n) {
    memset(isPrime, 1, sizeof(isPrime));
	minFactor[0] = minFactor[1] = -1;
	int sqrtn = (int)(sqrt(n));

	for (int i=2; i<=n; i++) minFactor[i] = i;

	for (int i=2; i<=sqrtn; i++) {
		if(minFactor[i] == i) {
			for (long long j=i*i; j<=n; j += i) {
                // 遇到尚未出现过的约数的数字就写入i值
				if(minFactor[j] == j) { // 因为保留最小的素因子
					minFactor[j] = i;
				}
			}
		}
	}
}

// 返回对大于2的自然数n的 素因子分解后的结果
vector<int> factorFast(int n) {
    vector<int> ret;
    while(n > 1) {
        ret.push_back(minFactor[n]);
        n /= minFactor[n];
    }
    return ret;
}


// 2. gcd : 最大公约数   lcm 最小公倍数
/// gcd(p, q) == gcd(p-q, q)
int gcd_simple(int p, int q) {
    if(p<q) std::swap(p, q);
	if(q == 0) return p;
	return gcd(p-q, q);
}

// 利用模运算更高效的算法
int gcd(int p, int q) {
	if(q == 0) return p;
	return gcd(q, p%q);
}

// 最小公倍数
// 分解质因数法:
    // 45=3*3*5
    // 30=2*3*5
    // lcm = 2*3*3*5 = 90

// 公式法:  a*b = gcd(a, b) * lcm(a, b)
long long lcm(int p, int q) {
	long long tmp = p*q;
	return tmp/gcd(p, q);
}

// 模运算:  加法 减法 乘法均成立
//  (a+b) % M = ((a%M) + (b%M)) % M
// P365 算法 韩 ===>   求数组 sum的后八位数字 , 对每一个元素进行取模 节省空间

// 容斥原理 +  扩展gcd  +  中国剩余定理 @acm 素数相关
int main () {
    for(auto i : factorSimple(9)) {
        cout << i << " ";
    }
    cout << endl;

    minFactorTable(10);
    for(auto i : factorFast(10)) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}