#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

const int MIN = numeric_limits<int>::min();
const int MAX = numeric_limits<int>::max();

// https://leetcode.com/problems/house-robber/discuss/156523/From-good-to-great.-How-to-approach-most-of-DP-problems.
// rob(n) = 当有n个房子要打劫, 能够得到最大收益
// a) rob current house i; b) don't rob current house.
// rob(n) = max (rob(n-2) + nums[n-1],   rob(n-1))
vector<int> cache(10, -1);
int rob(vector<int>& nums, int n) {
    // 错误处理
    int& ret = cache[n];
    if (n == 0) return ret = 0;
    if (n == 1) return ret = nums[n-1];

    if(ret != -1) return ret;
    return ret = max(rob(nums, n-2) + nums[n-1], rob(nums, n-1));
}

// bottom-up
int rob2(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // memo[i] 表示前i个房子抢完后 能够获得的最大收益
    vector<int> memo(n+1, -1);

    memo[0] = 0;
    memo[1] = nums[0];
    for (int i = 1; i < n; i++) {
        int val = nums[i];
        memo[i+1] = max(memo[i], memo[i-1] + val);
    }
    return memo[n];
}


// https://www.cnblogs.com/grandyang/p/4383632.html
int rob3(vector<int> &nums) {
    int rob = 0, notRob = 0, n = nums.size();
    for (int i = 0; i < n; ++i) {
        // preRob和preNotRob来分别记录更新之前的值
        int preRob = rob, preNotRob = notRob;
        // rob代表抢当前的房子
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