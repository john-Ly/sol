#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

const int MIN = numeric_limits<int>::min();
const int MAX = numeric_limits<int>::max();


// https://leetcode.com/problems/house-robber-ii/discuss/59934/Simple-AC-solution-in-Java-in-O(n)-with-explanation
// the solution is simply the larger of two cases with consecutive houses, i.e. house i not robbed, break the circle, solve it, or house i + 1 not robbed.
// 把连续的两户拆开 不成一个环
// 把第一家和最后一家分别去掉，各算一遍能抢的最大值，然后比较两个值取其中较大的一个即为所求
// https://www.cnblogs.com/grandyang/p/4518674.html
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return nums.empty() ? 0 : nums[0];
    return max(rob2(nums, 0, n-1), rob2(nums, 1, n));
}

int rob2(vector<int> &nums, int left, int right) {
    int rob = 0, notRob = 0;
    for (int i = left; i < right; ++i) {
        int preRob = rob, preNotRob = notRob;
        rob = preNotRob + nums[i];
        notRob = max(preRob, preNotRob);
    }
    return max(rob, notRob);
}

int main() {
    vector<int> v = {2,7,9,3,1};
    cout << rob(v, v.size()) << endl;
    cout << rob3(v) << endl;

    return 0;
}