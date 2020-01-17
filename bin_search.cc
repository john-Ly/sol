#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/6854825.html
//
// find 应该对应 左闭右开的区间
// lower_bound/ upper bound如果传入的区间范围 都是闭合的也无所谓 因为(循环体中存在相等的情况)

int find(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = (right + left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    return -1;
}

// std::lower_bound  worst_case lg(n) + 1 comparation
// 返回第一个不小于 目标的数
int find2(vector<int>& nums, int target) {
    // right = nums.size()-1 也可以运行程序
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = (right + left) / 2;
        // cout << nums[mid] << "--" << mid << '\n';
        // 1. 小于
        if (nums[mid] < target) left = mid + 1;
        // 2. 不小于
        // target == mid处的值应该作为右开边界 检查是否是第一个不小于
        // target <  mid处的值作为右开边界
        else right = mid;
    }
    return right;
    // right - 1最后一个小于目标的数
}


// 返回第一个大于 upper_bound
int find3(vector<int>& nums, int target) {
    // right = nums.size()-1 也可以运行程序
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = (right + left) / 2;
        if (nums[mid] <= target) left = mid + 1;
        else right = mid;
    }
    return right;
    // right - 1最后一个不大于目标的数
}


int main() {
    // vector<int> v = { 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 5, 5, 6 };
    vector<int> v = { 1, 1, 2, 3, 3, 3, 5, 5, 5, 5, 5, 6 };
    cout << "v.size: " << v.size() << '\n';
    cout << find(v, 6) << endl;

    // cout << find2(v, 3) << endl;
    // cout << find2(v, 5) << endl;
    // cout << find2(v, 6) << endl;

    cout << find3(v, 1) << endl;
    cout << find3(v, 4) << endl;
    cout << find3(v, 5) << endl;

    return 0;
}
