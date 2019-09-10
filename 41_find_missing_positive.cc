#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4395963.html
// 使用hash_set但 整数插入, 并且记录最大的
int firstMissingPositive1(vector<int>& nums) {
    int mx = 0;
    unordered_set<int> s;
    for (int num : nums) {
        if (num <= 0) continue;
        s.insert(num);
        mx = max(mx, num);
    }

    // 下次循环从1开始递增找数字，哪个数字找不到就返回哪个数字，如果一直找到了最大的数字，则返回最大值+1
    for (int i = 1; i <= mx; ++i) {
        if (!s.count(i)) return i;
    }
    return mx + 1;
}

// https://leetcode.com/problems/first-missing-positive/discuss/17071/My-short-c%2B%2B-solution-O(1)-space-and-O(n)-time
// 既然不能用hash 利用数组自身的下标当作 hash
// 把每个数放在正确的位置 A[i]= 5  那么A[4] = 5, 即交换 swap(A[4], A[i])
int firstMissingPositive (vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        //    正数  |          要在整个数组能够hash的范围
        // while 保证该位置存放的是合适的数字(除非不满足条件)
        // @TODO 很多空转 效率其实很低
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            swap(nums[i], nums[nums[i] - 1]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (nums[i] != i + 1) return i + 1;
    }
    return n + 1;
}


int main() {
    return 0;
}