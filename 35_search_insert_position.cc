#include <vector>
#include <iostream>
using namespace std;

// https://segmentfault.com/a/1190000008699980
// https://www.cnblogs.com/grandyang/p/6854825.html
// https://www.cnblogs.com/grandyang/p/4408638.html
// @TODO 二分查找这里基本搞清楚(还有upper, lower)
// 排序数组且没有重复
int searchInsert(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] >= target) return i;
    }
    return nums.size();
}

// 二分查找 mid计算  1.如果 lo+1=hi, mid=lo 2.lo+2=hi, mid=lo 3个数的中间那一个 3. lo=hi=mid
int searchInsert(vector<int>& nums, int target) {
    // 左闭右闭: 循环最后一个合理条件是 left=right，搜索空间压缩到一个数
    // 循环退出条件是 left = right+1 也就是两个指针交错
    // right->指向(如果数组存在这个数) target下标; left->指向target应该插入的位置

    // if (nums.back() < target) return nums.size();
    // int left = 0, right = nums.size() - 1;
    // while (left <= right) {
    //     int mid = left + (right - left) / 2;
    //     if (nums[mid] == target) return mid;
    //     else if (nums[mid] < target) left = mid + 1;
    //     else right = mid - 1;
    // }
    // return left;

    // 左闭右开: 循环最后一个合理条件是 left=right-1，搜索空间压缩到一个数
    // 循环退出条件是 left = right
    // left->指向(如果数组存在这个数) target下标; right->指向target应该插入的位置

    if (nums.back() < target) return nums.size();
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    return right;
}

int main() {
    vector<int> v {1,3,5,6};
    cout << searchInsert(v, 2) << endl;

    return 0;
}