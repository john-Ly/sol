#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

// 连续最大子数组求和
// @NOTE 题目要求: 不限事务交易次数(buy => sell)

// 计算每一个谷 峰(两个点 连续 compare consecutive elements)
// 时间 O(n)
int maxProfit(vector<int>& prices) {
    int maxprofit = 0;
    int valley = peak = prices[0];
    int i=0, size = prices.size();
    while()

    while (i < size - 1) {
        while (i < size-1 && prices[i] >= prices[i + 1])
            i++;
        valley = prices[i];  // 找到一个谷
        while (i < size-1 && prices[i] <= prices[i + 1])
            i++;
        peak = prices[i];
        maxprofit += peak - valley;
    }
    return maxprofit;
}

// https://www.cnblogs.com/grandyang/p/4280803.html
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/solution/
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/discuss/39038/Kadane's-Algorithm-Since-no-one-has-mentioned-about-this-so-far-%3A)-(In-case-if-interviewer-twists-the-input)


// 低价买入高价抛出
// 昨天买入，今日卖出，若明日价更高的话，还可以今日买入，明日再抛出。
int maxProfit1(vector<int> &prices) {
    int maxPro = 0;
    int n = prices.size();

    for (int i = 0; i < n - 1; ++i) {
        if (prices[i] < prices[i + 1]) {
            res += prices[i + 1] - prices[i];
        }
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