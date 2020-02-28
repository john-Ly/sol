#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4741122.html

// https://leetcode.com/problems/single-number-iii/discuss/68921/C%2B%2B-solution-O(n)-time-and-O(1)-space-easy-understaning-with-simple-explanation

// 两个数只出现一次, 求出这两个数
vector<int> singleNumber(vector<int>& nums) {
    int diff = 0;
    for (auto item : nums) diff ^= item;
    // 1. 此时diff = a^b  取出倒序第一个1
    // 快速取出 最低位 (最低位 即1000..的形式)
    // 40: 0010 1000  ==> 1000= 8 被取出来
    //          ----
    // 负数采用补码表示 各位取反 +1
    //
    int lastBit = diff & (-diff);  // 将两个数从低位起 不同的位作为区分
    int intA = 0, intB = 0;
    for (auto item : nums) {
        // 然后一次遍历 筛选出两个数(其他成对的数都会抵消掉)
        if (item & lastBit) intA ^= item;
        else intB ^= item;
    }

    return vector<int>{intA, intB};
}

int main () {
    vector<int> v {2,1,2};
    int tmp = singleNumber(v);

    std::cout << tmp << std::endl;
    return 0;
}
