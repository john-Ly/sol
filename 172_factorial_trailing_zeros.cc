// 求一个数的阶乘末尾0的个数
// 也就是找乘数中 10 的个数，10 = 2*5
// 仍需注意的一点就是，像 25，125，这样的不只含有一个5的数字需要考虑进去

// 阶乘保证 2的个数 多于 5的个数 因此5的个数确定 就是末尾0的个数

// https://www.cnblogs.com/grandyang/p/4219878.html
int trailingZeroes(int n) {
    int res = 0;
    while (n) {
        res += n / 5;
        n /= 5;
    }
    return res;
}