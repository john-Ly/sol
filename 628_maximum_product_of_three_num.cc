#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

const int MIN = numeric_limits<int>::min();
const int MAX = numeric_limits<int>::max();

// https://www.cnblogs.com/grandyang/p/7084957.html
int maximumProduct(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    // 仅针对 最后两个负数, 再和最大值进行相乘
    int cand1 = nums[0] * nums[1] * nums[n - 1];
    // 全是正数或者全是负数
    int cand2 = nums[n - 1] * nums[n - 2] * nums[n - 3];
    return max(cand1, cand2);
}

// 找出3个最大的数 || 找出一个最大的和两个最小的
int maximumProduct2(vector<int>& nums) {
    int mx1 = INT_MIN, mx2 = INT_MIN, mx3 = INT_MIN;
    int mn1 = INT_MAX, mn2 = INT_MAX;
    for (int num : nums) {
        if (num > mx1) {           // num > max1
            mx3 = mx2; mx2 = mx1; mx1 = num;
        } else if (num > mx2) {    // max1 > num > max2
            mx3 = mx2; mx2 = num;
        } else if (num > mx3) {    // max2 > num > max3
            mx3 = num;
        }

        if (num < mn1) {           // num < min1
            mn2 = mn1; mn1 = num;
        } else if (num < mn2) {    // min1 < num < min2
            mn2 = num;
        }
    }
    return max(mx1 * mx2 * mx3, mx1 * mn1 * mn2);
}