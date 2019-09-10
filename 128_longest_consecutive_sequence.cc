#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

// 官网解释还是最好的
// https://leetcode.com/problems/longest-consecutive-sequence/solution/
// 无序的数组里面找到 最长的连续子串(如 4 5 6 7 8...)

namespace so1 {
// time: O(n^3) space: O(1)
// 因为数组无序
bool arrayContains(vector<int>& arr, int num) {
    for(auto i: arr) {
        if (i==num) return true;
    }
    return false;
}

int longestConsecutive(vector<int>& nums) {
    int longestLen = 0;

    for (auto num : nums) {
        int current = num;
        int localLen = 1;

        while (arrayContains(nums, current+1)) {
            current++;
            localLen++;
        }

        longestLen = max(longestLen, localLen);
    }

    return longestLen;
}
}

namespace so2 {
// time: O(n lgn)
int longestConsecutive(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    sort(nums.begin(), nums.end());
    int longestLen = 0, localLen = 1;

    for (int i = 1; i < nums.size(); i++) {
        // 前后两数相等 重复 跳过, 否则判断是否连续
        if (nums[i] != nums[i-1]) {
            if (nums[i] == nums[i-1]+1) {
                localLen++;
            } else { // 连续序列终止(reset localLen, 重新统计)
                longestLen = max(longestLen, localLen);
                localLen = 1;
            }
        }
    }

    // 最后一行还要比较: 可能nums[n-1] 也被统计进localLen, 所以但是循环体的逻辑没有判断max
    return longestLen = max(longestLen, localLen);
}
}

namespace so3 {
// time: O(n lgn)
// https://leetcode.com/problems/longest-consecutive-sequence/discuss/41057/Simple-O(n)-with-Explanation-Just-walk-each-streak
// python的实现非常简洁
int longestConsecutive(vector<int>& nums) {
    // if (nums.size() == 0) return 0;
    // unordered_set<int> record(nums.begin(),nums.end());

    // int longestLen = 0;
    // for (auto i : nums) {
    //     // i是连续序列的起点
    //     if( record.find(i-1) == record.end() ) {
    //         int current = i;
    //         int localLen = 1;

    //         while( record.find(current+1) != record.end() ) {
    //             current++;
    //             localLen++;
    //         }

    //         longestLen = max(longestLen, localLen);
    //     }
    // }

    // return longestLen;

    if (nums.size() == 0) return 0;
    unordered_set<int> record(nums.begin(),nums.end());

    int longestLen = 0;
    for (auto i : nums) {
        // i是连续序列的起点
        if( record.find(i-1) == record.end() ) {
            int j = i+1;

            while( record.find(j) != record.end() )
                j++;

            longestLen = max(longestLen, j-i);
        }
    }

    return longestLen;

}
}

int main () {
    vector<int> v {100,4,200,1,3,2};
    cout << "brute-force: " << so1::longestConsecutive(v) << endl;
    cout << "sort: " << so2::longestConsecutive(v) << endl;
    cout << "hash_set: " << so3::longestConsecutive(v) << endl;

    return 0;
}