#include <iostream>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/5138186.html
// @see packing.cpp 背包问题属于最优问题 而非贪心
// 完全背包问题

// 使用最少的硬币 来组成 amount(每种面额的硬币无限)
// dp(amount) = min(dp(amount), dp(amount-coinsp[i]) + 1)
// 一块硬币 选和不选+ 选几个
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    // 把所有amount的子问题全部计算出来
    for (int i = 1; i <= amount; ++i) {
        // 确定选多少个硬币
        // @NOTE 没有排序 但是dp相当于把所有的可能都算出来更新到dp数组  -- 一个优化点 先从贪心(选面值尽可能大的硬币)
        for (int j = 0; j < coins.size(); ++j) {
            if (coins[j] <= i) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }

    // 看测试用例
    // Input: coins = [2], amount = 3
    // Output: -1
    return (dp[amount] > amount) ? -1 : dp[amount];
}