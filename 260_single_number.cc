#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4741122.html

// https://leetcode.com/problems/single-number-iii/discuss/68921/C%2B%2B-solution-O(n)-time-and-O(1)-space-easy-understaning-with-simple-explanation

vector<int> singleNumber(vector<int>& nums) {
    int diff = 0;
    for (auto item : nums) diff ^= item;
    diff &= -diff;  // 将两个数从低位起 不同的位作为区分
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
