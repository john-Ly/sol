#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4741028.html


// 求数根
int addDigits(int num) {
    while (num / 10 > 0) {
        // 每个digit累加
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

int addDigits2(int num) {
    return (num == 0) ? 0 : (num - 1) % 9 + 1;
}

int main() {
    cout << addDigits(38) << endl;
    return 0;
}