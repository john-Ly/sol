#include <iostream>
#include <vector>
using namespace std;

// @TODO 主要是溢出的问题 大数

int myPow(int x, int n) {
    int res = 1;
    // 偶数个表示 (x^2)^2...
    // 无论正数和负数 >>1 最终都会逼近0
    // @NOTE  i!=0 兼顾正负数
    //        i /= 2 负数也可以用 但是>>=1 会造成bug
    for(int i=n; i != 0; i /= 2) {
        if(i%2 != 0) res = res*x%1337;
        x *= x;
    }

    return res;
}

int superPow(int a, vector<int>& b) {
    long long res = 1;
    int sum = 0;
    for(int i=0; i<b.size(); ++i ) {
        sum *= 10;
        sum += b[i];
    }
    cout << sum << endl;

    for (int i = 0; i < b.size(); ++i) {
        res = myPow(res, 10) * myPow(a, b[i]) % 1337;
    }
    return res;
}

int main() {
    vector<int> v {1, 0};
    // 测试数据非常大  必定溢出
    cout << superPow(2, v) << endl;

    return 0;
}
