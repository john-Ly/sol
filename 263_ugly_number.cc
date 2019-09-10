#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4741934.html
// 所谓丑陋数就是其质数因子只能是2,3,5。那么最直接的办法就是不停的除以这些质数，如果剩余的数字是1的话就是丑陋数了

    bool isUgly(int num) {
        if (num <= 0) return false;
        while (num % 2 == 0) num /= 2;
        while (num % 3 == 0) num /= 3;
        while (num % 5 == 0) num /= 5;
        return num == 1;
    }
