#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4756677.html
// @SEE single number

// 0-n 所有的数都 ^ 然后缺失的数自然就出来了
// 相同数字异或为0
int missingNumber3(vector<int>& nums) {
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        res ^= (i + 1) ^ nums[i];
    }
    return res;
}

// https://leetcode.com/problems/missing-number/solution/
// 如果数组已经排序 使用二分查找也很快
int missingNumber2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    // right 右开区间
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = (left + right) / 2;
        // 元素大于下标  说明缺失的数字在左边
        if (nums[mid] > mid) right = mid;
        else left = mid + 1;
    }
    return right;
}

// 可以参考41 find missing positive(数组本身作为 hash)
int missingNumber1(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        // 使用while循环 保证i 这个位置存放的一定是合适的数字(除非不满足条件)
        // @SEE 41为什么要使用while
        while(nums[i] < n && nums[nums[i]] != nums[i])
            swap(nums[i], nums[nums[i]]);
    }
    for (int i = 0; i < n; ++i) {
        if (nums[i] != i) return i;
    }
    return n;
}

// 高斯求和
int missingNumber4(vector<int>& nums) {
    int sum = 0, n = nums.size();
    for (auto &a : nums) {
        sum += a;
    }
    return 0.5 * n * (n + 1) - sum;
}

int main () {
    vector<int> v = {9,6,4,2,3,5,7,0,1};
    cout << missingNumber1(v) << endl;

    return 0;
}