#include <iostream>
#include <climits>  // INT_MAX INT_MIN
using namespace std;

//  int: min         max
//  -2147483648	  2147483647
// 1. 整数的每一位
//     while (x)
//       int lst = x%10;
//       x /= 10;
// @NOTE  / 负数进行除法得到的商  要向0取整
//        e.g.:   (-13)/4 = -3  而不是-4
//        % 取模得到的余数 一定是正

namespace reverse_int {
// @NOTE leetcode上的答案很经典
// Reversing an integer can be done similarly to reversing a string.
// We want to repeatedly "pop" the last digit off of xx and "push" it to the back of the rev. In the end, rev will be the reverse of the xx.
// To "pop" and "push" digits without the help of some auxiliary stack/array, we can use math.
//     //pop operation:
//     pop = x % 10;
//     x /= 10;

//     //push operation:
//     temp = rev * 10 + pop;
//     rev = temp;
int reverse(int x) {
    int y = 0;
    while (x != 0) {
        int n = x % 10;
        // Checking the over/underflow.
        //
        // INT_MAX: 214748364 7
        // 2147483642  ==> 0   因为21..42 前一个条件就满足类这种不可能(数学上可能严谨 但是int计算机实现还是有限制)
        if (y > INT_MAX/10 /* || (y == INT_MAX/10 && n > 7)*/) return 0;
        if (y < INT_MIN/10 /* || (y == INT_MIN/10 && n < -8)*/) return 0;

        y = y * 10 + n;
        x /= 10;
    }
    return y;
}


}

namespace atoi_itoa {
}

//   https://leetcode.com/problems/palindrome-linked-list/discuss/64490/My-easy-understand-C%2B%2B-solution
// 2. http://www.cnblogs.com/grandyang/p/4125510.html

// 取出后半部分 进行翻转 前后相等就是回文数字(分偶数 和 奇数个位)
// 最好方法
namespace  {
bool isPalindrome2(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;
    int revertNum = 0;
    // @TODO 这个判断条件的依据是?
    while (x > revertNum) {
        revertNum = revertNum * 10 + x % 10;
        x /= 10;
    }
    return x == revertNum /*偶数*/ || x == revertNum / 10 /*奇数*/;
}

bool isPalindrome3(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;
    return reverse(x) == x;
}

int reverse(int x) {
    int res = 0;
    while (x != 0) {
        // 溢出肯定不是回文
        if (res > INT_MAX / 10) return -1;
        res = res * 10 + x % 10;
        x /= 10;
    }
    return res;
}
}


// 针对每一对 进行比较
bool isPalindrome(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) return false;
    int div = 1;
    while (x / div >= 10) div *= 10; // 确定div 取得数组的最高位

    int l, h;
    while (x > 0) {
        h = x / div;
        l = x % 10;
        if (l != h) return false;
        x = (x % div) / 10;
        div /= 100;   // 每次要消耗两位
    }
    return true;
}


int main() {

}
