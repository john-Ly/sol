#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4800552.html
// 数学题目 面试概率低
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


int main () {

    cout << endl;
    return 0;
}