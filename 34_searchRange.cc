#include <vector>
#include <iostream>
using namespace std;
// https://www.cnblogs.com/grandyang/p/4409379.html

// https://www.cnblogs.com/grandyang/p/6854825.html
// lower+upper
vector<int> searchRange(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> res(2, -1);
    if(n < 1) return res; // 不合法

    int left = 0, right = n;

    //可能存在多个target 或者 不存在target
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1; // 向右压缩
        else right = mid;     // 向左压缩
    }
    // {2, 2} target=3
    if (right == n || nums[right] != target) return res;

    res[0] = right; // lower_bound
    if(n==1) {
        res[1] = right;
        return res;
    }
    right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) left = mid + 1;
        else right= mid;
    }
    res[1] = right - 1;
    return res;
}

int main() {
    vector<int> v {2,2};
    auto tmp = searchRange(v, 3);
    cout << tmp[0] << " " << tmp[1] << endl;

    return 0;
}