#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/6854825.html
// 二分搜索法的关键在于获得了中间数后，判断下面要搜索左半段还是右半段
// 数组按照升序排列(中间数和右边进行比较)
// 如果中间的数小于最右边的数，则右半段是有序的，若中间数大于最右边数，则左半段是有序的
// 我们只要在有序的半段里用首尾两个数组来判断目标值是否在这一区域内，这样就可以确定保留哪半边了

// 二分法只适用与有序的数组 为什么下面的算法可行 @TODO

// 判断mid是在 pivot左侧 还是右侧 @TODO 配图 + 和旋转数组 比较来看
// https://www.cnblogs.com/grandyang/p/4325648.html
// https://leetcode.com/problems/search-in-rotated-sorted-array/discuss/14436/Revised-Binary-Search/191339
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = (right + left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < nums[right]) {// nums[mid] 在 pivot右边 右半段有序
            if (nums[mid] < target && nums[right] >= target) left = mid + 1;
            else right = mid - 1;
        } else {  // 左半段 有序 (mid在pivot左边)
            if (nums[left] <= target && nums[mid] > target) right = mid - 1;
            else left = mid + 1;
        }
    }
    return -1;
}

// https://www.cnblogs.com/grandyang/p/4325840.html
// 如果源数组存在重复 只需要在最后一行加上(--right)逻辑
bool search_dup(vector<int>& nums, int target) {
    int n = nums.size(), left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) return true;
        if (nums[mid] < nums[right]) {
            if (nums[mid] < target && nums[right] >= target) left = mid + 1;
            else right = mid - 1;
        } else if (nums[mid] > nums[right]){
            if (nums[left] <= target && nums[mid] > target) right = mid - 1;
            else left = mid + 1;
        } else --right;
    }
    return false;
}

int main() {
    vector<int> v {4,5,6,7,0,1,2};
    vector<int> v2 {2,5,6,0,0,1,2};
    cout << search(v, 0) << endl;
    cout << search_dup(v2, 0) << endl;

    return 0;
}

