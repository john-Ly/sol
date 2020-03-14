#include <iostream>
#include <limits.h>
#include <math.h>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4431949.html

// dividend 被除数  divisor 除数
int divide(int dividend, int divisor) {
    // 溢出的情况             被除数数INT_MIN  除数是-1 但是正数的范围  abs(INT_MAX) + 1 = abs(INT_MIN)
    if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
    long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;

    // @TODO 位运算  异或
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    if (n == 1) return sign == 1 ? m : -m;
    while (m >= n) {
        // 最后一个余数 
        long long t = n, p = 1;
        // 偶数个余数
        while (m >= (t << 1)) {
            t <<= 1;
            p <<= 1;
        }
        res += p;
        m -= t;
    }
    return sign == 1 ? res : -res;
}

int main() {
    cout << divide(INT_MIN, -1) << endl;
    cout << divide(INT_MIN, 0) << endl;
    cout << divide(10, 3) << endl;
    cout << divide(10, 1) << endl;

    return 0;
}
