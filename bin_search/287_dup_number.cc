#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// n+1 个数,  每个数范围 [1, n]
// 要求: nums不能修改 O(n lgn)  upper_bound O(n^2) + space O(1)

// https://leetcode.com/problems/find-the-duplicate-number/solution
int findDuplicate1(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    // 排序之后 直接找到重复的数字
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i-1]) {
            return nums[i];
        }
    }

    return -1;
}

// 可以使用hash_set 但是空间复杂度超过 O(1)要求

// 在1-n的范围里面进行二分搜索
// https://leetcode.com/problems/find-the-duplicate-number/discuss/72844/Two-Solutions-(with-explanation)%3A-O(nlog(n))-and-O(n)-time-O(1)-space-without-changing-the-input-array
int findDuplicate(vector<int>& nums) {
    int left = 0, right = nums.size(); // [0, n] 表示n+1个数字
    // 最终搜索空间会收敛到 left=right
    while (left < right){
        int mid = (right + left) / 2, cnt = 0;
        cout << mid << endl;
        for (int num : nums) {
            if (num <= mid) ++cnt;
        }
        if (cnt <= mid) left = mid + 1;  // 一定重复的不出现在1..mid
        else right = mid; // 一定有一个重复的出现在 1...mid
    }
    return right;
}

// https://www.cnblogs.com/grandyang/p/4843654.html
// https://www.cnblogs.com/hiddenfox/p/3408931.html
// 链表环的起点的求法
// @TODO 不理解
int findDuplicate2(vector<int>& nums) {
    int slow = 0, fast = 0, t = 0;
    // slow/fast
    while (true) {
        slow = nums[slow];
        fast = nums[nums[fast]];
        if (slow == fast) break;
    }

    while (true) {
        slow = nums[slow];
        t = nums[t];
        if (slow == t) break;
    }
    return slow;
}

int main() {
    vector<int> v = {3,1,3,4,2};
    auto t = findDuplicate(v);

    cout << t << endl;
    return 0;
}