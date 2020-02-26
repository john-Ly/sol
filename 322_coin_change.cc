#include <iostream>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/5138186.html
// @SEE packing.cc 背包问题属于最优问题 而非贪心
// 完全背包问题

namespace sol_brute {
// 重复子问题很严重
int process1(vector<int>& coins, int index, int amount) {
    int res = 0;
    if (index == coins.size()) {
        res = (amount == 0 ? 1 : 0);
    } else {
        for (int i=0; coins[index]*i <= amount; ++i) {
            res += process1(coins, index+1, amount-coins[index]*i);
        }
    }
}

int coinChange(vector<int>& coins, int amount) {
    if (coins.empty() || amount <= 0) return 0;
    return process1(coins, 0, amount);
}
}

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