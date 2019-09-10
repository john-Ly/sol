#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4315649.html
// 直接排列的方法还是太麻烦
// @TODO 考虑使用std::bitset看看有没有帮助


// https://zhuanlan.zhihu.com/p/29254973 详细的图示 bin_gray的算法
// https://www.cnblogs.com/grandyang/p/4315607.html  wiki上的算法
unsigned int binaryToGray(unsigned int num) {
        return (num >> 1) ^ num;
}

unsigned int grayToBinary(unsigned int num) {
    unsigned int mask;
    // 因为每一位都要累加异或 所以有for循环
    for (mask = num >> 1; mask != 0; mask = mask >> 1) {
        num = num ^ mask;
    }
    return num;
}

// 二进制到格雷码的转换
vector<int> grayCode(int n) {
    vector<int> res;
    int nums = (unsigned int)1 << n;
    for (int i = 0; i < nums; ++i) {
        res.push_back((i >> 1) ^ i);
    }
    return res;
}