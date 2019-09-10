#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

//
// @NOTE 题目要求: 事务交易次数为最多2(buy => sell)
// 允许一天内买进和卖出(相当于不交易)
// http://bangbingsyb.blogspot.com/2014/11/leetcode-best-time-to-buy-and-sell.html

// prices[0:n-1] => prices[0:i] + prices[i:n-1]

int maxProfit(vector<int> &prices) {
    if (prices.size() < 2) return 0;
    int maxPro = 0;
    const int n = prices.size();
    vector<int> leftPro(n, 0);

    int maxLeftPro = 0, minPrice = prices[0];
    for(int i=1; i<n; i++) {
        minPrice = min(minPrice, prices[i]);
        maxLeftProfit = max(maxLeftPro, prices[i]-minPrice);
        leftPro[i] = maxLeftPro;
    }
    // leftPro[0] 统计没有意义  因为第一天进行交易利润最大是0

    maxPro = leftPro[n-1];
    int maxRightPro = 0, maxPrice = prices[n-1];
    for(int i=n-2; i>=0; i--) {
        maxPrice = max(maxPrice, prices[i]);
        // 还是能计算
        maxRightPro = max(maxRightProfit, maxPrice-prices[i]);

        maxPro = max(maxPro, maxRightProfit + leftProfit[i]);
    }


    /*  最大m段子和 == 差分数组
    vector<int> f(n, 0);
    vector<int> g(n, 0);
    for (int i = 1, valley = prices[0]; i < n; ++i) {
        valley = min(valley, prices[i]);
        f[i] = max(f[i - 1], prices[i] - valley);
    }
    for (int i = n - 2, peak = prices[n - 1]; i >= 0; --i) {
        peak = max(peak, prices[i]);
        g[i] = max(g[i], peak - prices[i]);
    }

    int maxPro = 0;
    for (int i = 0; i < n; ++i)
        maxPro = max(maxPro, f[i] + g[i]);
    */
    return maxPro;
}

int main () {
    vector<int> v {7, 1, 5, 3, 6, 4};
    vector<int> v1 {7, 1, 3, 6, 4};
    int max = maxProfit1(v);

    cout << max << endl;
    return 0;
}