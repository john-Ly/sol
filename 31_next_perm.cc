#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4428207.html
// https://leetcode.com/problems/next-permutation/solution/
// 动画演示
/*
1 　*2*　　7　　4　　3   1    逆序: 找到第一个不按照升序的数字 pivote
1 　*2*　　7　　4   *3*  1    逆序: 找到第一个 大于pivote的数字下标
1 　*3*　　7　　4   *2*  1    交换下标 i, j
1 　 3    *1　　2    4   7*
*/

// orig: 1 2 7 4 3 1
// prev: 1 2 7 4 1 3
// next: 1 3 1 2 4 7

void nextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 2, j = n - 1;
    while (i >= 0 && nums[i] >= nums[i + 1]) --i;
    if (i >= 0) {
        while (nums[j] <= nums[i]) --j;
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}

// @TODO 逻辑没有搞清楚
void prePermutation(vector<int>& nums) {
    int n = nums.size(), i = 0, j = 1;
    while (j < n && nums[j] >= nums[j-1]) ++j;
    if (j < n) {
        while (nums[j] >= nums[i]) ++i;
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + j + 1, nums.end());
}