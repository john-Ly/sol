#include <stdint.h>
#include <vector>
// https://www.cnblogs.com/grandyang/p/4217175.html

// 需要修改源数组
int findPeakElement1(vector<int>& nums) {
    // corner-case: 数组只有一个数且INT_MIN
    if (nums.size() == 1) return 0;
    nums.insert(nums.begin(), INT_MIN);
    nums.push_back(INT_MIN);
    for (int i = 1; i < (int)nums.size() - 1; ++i) {
        if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) return i - 1;
    }
    return -1;
}

// 前提是 相邻的两个数字不会相等
// Time: O(n)
int findPeakElement2(vector<int>& nums) {
    // 如果第二个数字小于 第一个 说明局部峰值出现(像雨天能接多少水)
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < nums[i - 1]) return i - 1;
    }
    return nums.size()-1;
}

// https://leetcode.com/problems/find-peak-element/solution/
// 采用二分法的变形(有点贪心的感觉)
// 递增序列/ 递减序列/ mix   主要看斜率
int findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        // 说明当前点处于递增的线段 峰值在右边范围
        if (nums[mid] < nums[mid + 1]) left = mid + 1;
        // 递减 峰值在左边
        else right = mid;
    }
    return right;
}