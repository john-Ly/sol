#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

// https://leetcode.com/problems/unique-paths/discuss/22954/C%2B%2B-DP
//  从 空间复杂度逐步分析
// 常规的dp思路 是从dp(0,0) -> dp(i,j)
// 递归的思路是  dp(i,j) -> dp(i+1, j+1)   要先假设已经有了dp(i, j)

// https://leetcode.com/problems/unique-paths/discuss/22958/Math-solution-O(1)-space
// 实际是一个组合问题 C(m+n, m+n) @TODO
// https://www.cnblogs.com/grandyang/p/4353555.html

template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{\n";
	for (vector<T> row: mat) {
        cout << "  [";
		for (T val: row) {
			cout << val << " , ";
		}
        cout << "],\n";
	}
    cout << "}\n";
}

namespace so1 {
int m = 7; int n = 3;
vector<vector<int>> cache(m+1, vector<int>(n+1, -1));
// 自顶向下dp 递归
// uniquePaths(y, x) = 返回从(y, x)其实到最终目标的子路径的个数
int uniquePaths(int y, int x) {
    int& ret = cache[y][x];
    // 异常部分; y合法范围 [0, m-1] x同理
    if(y >= m || x >= n) return ret = 0;
    if(y == m-1 && x == n-1) return ret = 1;

    if(ret != -1) return ret;

    return ret = uniquePaths(y, x+1) + uniquePaths(y+1, x);
}
}

namespace so2 {
// uniquePaths(y, x) = 返回从(y, x)其实到最终目标的子路径的个数
int uniquePaths_iter(int m, int n) {
    // 初始化1 保证(0,x) 和 (y,0) 的下标 路径个数都是确定的 1条
    vector<vector<int>> dp(m, vector<int>(n, 1));

    for (int i = m-2; i >= 0 ; i--) {
        for (int j = n-2; j >= 0; j--) {
            //         向下走        向右走
            dp[i][j] = dp[i+1][j] + dp[i][j+1];
        }
    }

    printVector(dp);
    return dp[0][0];
}

int uniquePaths_iter2(int m, int n) {
    // 初始化1 保证(0,x) 和 (y,0) 的下标 路径个数都是确定的 1条
    vector<vector<int>> dp(2, vector<int>(n, 1));

    for (int i = m-2; i >= 0 ; i--) {
        for (int j = n-2; j >= 0; j--) {
            //         向下走        向右走
            dp[i%2][j] = dp[(i+1)%2][j] + dp[i%2][j+1];
        }
    }

    // printVector(dp);
    return dp[0][0];
}
}

// bottom up
namespace so3 {
// uniquePaths(i, j) = 返回从起点到 (i, j)路径的个数
// m行 n列   Time/Space O(m*n)
int uniquePaths_iter_bottom_up(int m, int n) {
    // 初始化1 保证(0,x) 和 (y,0) 的下标 路径个数都是确定的 1条
    vector<vector<int>> dp(m, vector<int>(n, 1));

    for (int i=1; i<m; ++i) {
        for (int j=1; j<n; ++j) {
            //         来自左边      来自右边
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}

int uniquePaths_iter_bottom_up2(int m, int n) {
    // 初始化1 保证(0,x) 和 (y,0) 的下标 路径个数都是确定的 1条
    vector<int> pre(n, 1), cur(n, 1);

    for (int i=1; i<m; ++i) {
        for (int j=1; j<n; ++j) {
            //       上一行    下一行
            cur[j] = pre[j] + cur[j-1];
        }
        swap(pre, cur);
    } // 循环退出后 cur失效 pre为最新的一行

    return pre[n-1];
}

// 还有更新的可能? 如果只要单层循环 就可以使用仅仅两个变量
int uniquePaths_iter_bottom_up3(int m, int n) {
    vector<int> cur(n, 1);

    // 因为只需要更新两行: pre来更新下一行
    // 初始化已经包含了第一行和低一列
    for (int i=1; i<m; ++i) {
        for (int j=1; j<n; ++j) {
            // cur[j] 在更新前就是pre[j]
            cur[j] += cur[j-1];
        }
    } // 循环退出后 cur失效 pre为最新的一行

    return cur[n-1];
}
}

// leetcode 63 有障碍物
namespace so4 {
// uniquePaths(i, j) = 返回从起点到 (i, j)路径的个数 if: obstacleGrid(i,j)==0
// obstacleGrid 0/1矩阵 障碍物表示为1
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid[0][0] == 1) return 0;
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<long>> dp(m + 1, vector<long>(n + 1, 0));
    dp[0][1] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (obstacleGrid[i-1][j-1] == 0)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[m][n];
}

// https://www.cnblogs.com/grandyang/p/4353680.html
// https://leetcode.com/problems/unique-paths-ii/discuss/23252/4ms-O(n)-DP-Solution-in-C%2B%2B-with-Explanations
int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid[0][0] == 1) return 0;
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    // 某一行中各列 dp[i, j] 从起点到i,j路径的个数
    vector<long> dp(n, 0);
    dp[0] = 1; // 第一行第一列为1, 保证
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[i][j] == 1) dp[j] = 0;
            else if (j > 0) dp[j] += dp[j - 1];
        }
    }
    return dp[n - 1];
}
}

int main() {
    // std::memset(cache, -1, sizeof(cache));
    {
        using namespace so1;
        cout << uniquePaths(0, 0) << endl;
        printVector(cache);
    }

    {
        using namespace so2;
        cout << uniquePaths_iter(so1::m, so1::n) << endl;
        cout << uniquePaths_iter2(so1::m, so1::n) << endl;
    }

    return 0;
}