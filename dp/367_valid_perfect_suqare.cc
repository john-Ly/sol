#include <iostream>
#include <limits.h>
#include <math.h>
using namespace std;

// https://www.cnblogs.com/grandyang/p/5619296.html

// 以指数的速度来缩小范围
// 比如一个数字49，我们先对其除以2，得到24，发现24的平方大于49，那么再对24除以2，得到12，发现12的平方还是大于49，再对12除以2，
// 得到6，发现6的平方小于49，于是遍历6到12中的所有数，看有没有平方等于49的，有就返回true，没有就返回false
bool isPerfectSquare(int num) {
    if (num == 1) return true;

    // 对半逼近
    long x = num / 2, t = x * x;
    while (t > num) {
        x /= 2;
        t = x * x;
    }
    // 循环之后 x^2<num  (2x)^2 > num
    for (int i = x; i <= 2 * x; ++i) {
        if (i * i == num) return true;
    }
    return false;
}

bool isPerfectSquare1(int num) {
    if(num == 1) return true;
    int left = 0, right = num;
    while (left < right) {
        int mid = (right + left) / 2;
        long t = mid*mid;
        cout << mid << "-" << t << endl;
        if (t == num) return true;
        else if (t < num) left = mid + 1;
        else right = mid;
    }

    cout <<"====" << endl;
    return false;
}

int main() {
    cout << isPerfectSquare1(1)  << endl;

    return 0;
}
