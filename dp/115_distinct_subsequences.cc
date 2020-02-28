#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 详细的解释 DP
// 什么是动态规划（Dynamic Programming）？动态规划的意义是什么？ - 王勐的回答 - 知乎
// https://www.zhihu.com/question/23995189/answer/35429905
// 计算机的本质是状态机
// 每个阶段只有一个状态->递推
// 每个阶段的最优状态都是由上一个阶段的最优状态得到的->贪心
// 每个阶段的最优状态是由之前所有阶段的状态的组合得到的->搜索
// 每个阶段的最优状态可以从之前某个阶段的某个或某些状态直接得到而不管之前这个状态是如何得到的->动态规划。

// https://leetcode.com/problems/distinct-subsequences/discuss/37316/7-10-lines-C%2B%2B-Solutions-with-Detailed-Explanations-(O(m*n)-time-and-O(m)-space)
// https://leetcode.com/problems/distinct-subsequences/discuss/37327/Easy-to-understand-DP-in-Java
// 问题: numDistinct[i][j] = 在s的[0, j-1] j个字符范围中 包含 t[0, i-1] i个字符范围的 不同的个数
//       子问题可以在进行拆解
//  @SEE 上面链接的图解


// space: O(m*n)
int numDistinct1(string s, string t) {
    int m = t.length(), n = s.length();
    vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));

    // t is empty string
    for (int j = 0; j <= n; j++) dp[0][j] = 1;

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            if (t[i-1] == s[j-1]) {   //  当前字符相等(要考虑上一个t[i-1]的效果 类似指数增长 a-b 有两条路 b-c 有3条路   a-c 有几条路    动态规划找出最短的一条路)
                dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
            } else {                  // 说明这个字符是无效字符
                dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[m][n];
}

// space: O(m)
int numDistinct2(const string& s, const string& t) {
    int m = t.length(), n = s.length();
    vector<int> cur(m + 1, 0);   // 相当于上一中解法中 只保留行信息
    cur[0] = 1;
    for (int j = 1; j <= n; j++) {  // s
        int pre = 1;
        for (int i = 1; i <= m; i++) {
            int temp = cur[i];
            cur[i] = cur[i] + (t[i - 1] == s[j - 1] ? pre : 0);
            pre = temp;
        }
    }
    for(auto i: cur) cout << i << " ";
    cout <<  endl;
    return cur[m];
}

int main() {
    string s = "acdabefbc";
    string t = "ab";

    cout << numDistinct2(s, t) << endl;

    return 0;
}