#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/solution/
//
// @NOTE 题目要求: 只能完成一笔事务交易(buy => sell)

// 每一个差值都要计算
int maxProfit(vector<int>& prices) {
    int maxprofit = 0;
    for (int i = 0; i < prices.size() - 1; i++) {
        for (int j = i + 1; j < prices.size(); j++) {
            int profit = prices[j] - prices[i];
            maxprofit = std::max(maxprofit, profit);
        }
    }
    return maxprofit;
}

// 找到最低价格和最大的差值（只有先买进才能卖出  所以数值的顺序必须是正向的）
// 直觉:先找到最小的数（因为最大的利润只在最小的数字之后）,再顺序求出最大的利润即可
//
// 两个变量分别记录
// 用一个变量记录遍历过数中的最小值，然后每次计算当前值和这个最小值之间的差值为利润
// 然后每次选较大的利润来更新。

// 局部最优和全局最优
int maxProfit1(vector<int> &prices) {
    int maxPro = 0;
    int minPrice = std::numeric_limits<int>::max();
    for(int i = 0; i < prices.size(); i++){
        minPrice = std::min(minPrice, prices[i]);
        maxPro = std::max(maxPro, prices[i] - minPrice);
    }
    return maxPro;
}

int main () {
    vector<int> v {7, 1, 5, 3, 6, 4};
    vector<int> v1 {7, 1, 3, 6, 4};
    int max = maxProfit1(v);

    cout << max << endl;
    return 0;
}