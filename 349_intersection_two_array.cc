#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/5507129.html
// 二分法查找总结
// https://www.cnblogs.com/grandyang/p/6854825.html

// 两个数组交集的部分（不包含重复数字）
// @TODO STL容器 之间相互 构造函数
vector<int> intersection1(vector<int>& nums1, vector<int>& nums2) {
    set<int> s(nums1.begin(), nums1.end()), res;
    for (auto a : nums2) {
        if (s.count(a)) res.insert(a);
    }
    return vector<int>(res.begin(), res.end());
}

vector<int> intersection2(vector<int>& nums1, vector<int>& nums2) {
    vector<int> res;
    int i = 0, j = 0;
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] < nums2[j]) ++i;
        else if (nums1[i] > nums2[j]) ++j;
        else {
            //   首次加入   ||    不重复
            if (res.empty() || res.back() != nums1[i]) {
                res.push_back(nums1[i]);
            }
            ++i; ++j;
        }
    }
    return res;
}

// 二分查找只适用于  排序数组
bool binarySearch(vector<int> &nums, int target) {
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = (right + left) / 2;
        if (nums[mid] == target) return true;
        else if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    return false;
}

vector<int> intersection3(vector<int>& nums1, vector<int>& nums2) {
    set<int> res;
    sort(nums2.begin(), nums2.end());
    for (auto a : nums1) {
        if (binarySearch(nums2, a)) {
            res.insert(a);
        }
    }
    return vector<int>(res.begin(), res.end());
}

int main() {
return 0;
}
