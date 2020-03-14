#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4383775.html
// 除数和被除数那道题很相似

// @NOTE 只针对整数的情形
// 每次2的幂次进行
// 2^9 = 2^8 * 2^1
int Qpow(int a,int n) {
    int ans = 1;
    // 判断 n中 1的个数
    while(n) {
        if(n&1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

// 让i初始化为n，然后看i是否是2的倍数
// 是: x乘以自己
// 否则: res乘以x，i每次循环缩小一半，直到为0停止循环。
double myPow(double x, int n) {
    double res = 1.0;
    // 偶数个表示 (x^2)^2...
    // 无论正数和负数 >>1 最终都会逼近0
    // @NOTE  i!=0 兼顾正负数
    //        i /= 2 负数也可以用 但是>>=1 会造成bug
    for(int i=n; i != 0; i /= 2) {
        if(i%2 != 0) res *= x;
        x *= x;
    }

    return n<0 ? 1/res : res;
}

int main() {
    cout << myPow(2.00000, 10) << endl;
    cout << myPow(2.10000, 3) << endl;
    cout << myPow(2.00000, -2) << endl;

    return 0;
}
