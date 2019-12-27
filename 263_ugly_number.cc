#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4741934.html
// 所谓丑陋数就是其质数因子只能是2,3,5。那么最直接的办法就是不停的除以这些质数，如果剩余的数字是1的话就是丑陋数了

// https://www.cnblogs.com/grandyang/p/4743837.html
// 找到丑数序列的 第几个( @TODO)


bool isUgly(int num) {
    if (num <= 0) return false;
    while (num % 2 == 0) num /= 2;
    while (num % 3 == 0) num /= 3;
    while (num % 5 == 0) num /= 5;
    return num == 1;
}

// https://www.cnblogs.com/grandyang/p/4800552.html
// 完全平方数 感觉是数学概念题目 (@TODO)
int numSquares(int n) {
    while (n % 4 == 0) n /= 4;
    if (n % 8 == 7) return 4;
    for (int a = 0; a * a <= n; ++a) {
        int b = sqrt(n - a * a);
        if (a * a + b * b == n) {
            return !!a + !!b;
        }
    }
    return 3;
}