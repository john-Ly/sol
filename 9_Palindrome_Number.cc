#include <iostream>
#include <climits>
using namespace std;
// 1. 类似 链表判断回文 但是(链表的个数可以确定 但是数组的位数使用递归有点麻烦)
//   https://leetcode.com/problems/palindrome-linked-list/discuss/64490/My-easy-understand-C%2B%2B-solution
// 2. http://www.cnblogs.com/grandyang/p/4125510.html


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

// 取出后半部分 进行翻转 前后相等就是回文数字(分偶数 和 奇数个位)
// 最好方法
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


int main() {

}
