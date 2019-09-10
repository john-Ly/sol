#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4032934.html
// int findMin(vector<int> &num) {
//     int left = 0, right = num.size() - 1;
//     if (num[left] > num[right]) {
//         while (left != (right - 1)) {
//             int mid = (left + right) / 2;
//             if (num[left] < num[mid]) left = mid;
//             else right = mid;
//         }
//         return min(num[left], num[right]);
//     }
//     return num[0];
// }

// @TODO 二分查找 真的需要想明白
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/discuss/48484/A-concise-solution-with-proof-in-the-comment
int findMin(vector<int> &num) {
    int low = 0, high = num.size() - 1;
    // loop invariant: 1. low < high
    //                 2. mid != high and thus A[mid] != A[high] (no duplicate exists)
    //                 3. minimum is between [low, high]
    // The proof that the loop will exit: after each iteration either the 'high' decreases
    // or the 'low' increases, so the interval [low, high] will always shrink.
    while (low < high) {
        auto mid = low + (high - low) / 2;
        if (num[mid] < num[high]) // num[mid]一定在pivot的右边 右边是升序
            // the mininum is in the left part
            high = mid; // 可能mid是就是最低点 所以high = mid
        else if (num[mid] > num[high])  // num[mid]一定在pivot的左边 左边是升序
            // the mininum is in the right part
            low = mid + 1;
    }

    return num[low];
}


int findMin_dup(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        auto mid = low + (high - low) / 2;
        if (nums[mid] < nums[high]) // num[mid]一定在pivot的右边 右边是升序
            high = mid; // 可能mid是就是最低点 所以high = mid
        else if (nums[mid] > nums[high])  // num[mid]一定在pivot的左边 左边是升序
            low = mid + 1;
        else { high--; }
    }

    return nums[low];

}

int main() {
    vector<int> v {1, 2, 2, 3};
    cout << find2(v, 2) << endl;
    cout << find3(v, 2) << endl;

    return 0;
}