#include <iostream>
#include <vector>
#include <cstring>
#include <climits>  // INT_MAX
#include <algorithm>
using namespace std;

//  最优问题: 最小值  初始值可以调整成INT_MAX

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

vector<vector<int>> grid = {
		{1,3,1},
		{1,5,1},
		{4,2,1},
	};

int m = grid.size(); int n = grid[0].size();

// path2(y, x) = 返回从(y, x)起始到最后一行的子路径(剩余子问题)总和的最大值
// time: O(2^ n)  @TODO P148 求解二项式系数的问题 时间复杂度 子问题的个数是 O(n^2)(还有杨辉三角)

namespace so1 {
vector<vector<int>> cache(m+1, vector<int>(n+1, -1));
int path2(int y, int x) {
	if(y >= m || x >= n) return INT_MAX; // 因为最终会比较 min 所以一定要设置INT_MAX
    int& ret = cache[y][x];
    if (y == m-1 && x == n-1) return ret = grid[y][x];

	if(ret != -1) return ret;
	return ret = min(path2(y, x+1), path2(y+1, x)) + grid[y][x];
}
}

// 推荐做法
namespace so2 {
class Solution {
public:
    // bottom-up 比较容易理解
    // https://leetcode.com/problems/minimum-path-sum/discuss/23457/C%2B%2B-DP
    // 从起点到(i,j)最小路径长度 S[i][j] = min(S[i-1][j], S[i][j-1]) + grid[i][j]
    int minPathSum1(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int> > sum(m, vector<int>(n, grid[0][0]));

        for (int i = 1; i < m; i++)  // 第1列
            sum[i][0] = sum[i-1][0] + grid[i][0];
        for (int j = 1; j < n; j++)  // 第1行
            sum[0][j] = sum[0][j - 1] + grid[0][j];

        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                sum[i][j]  = min(sum[i- 1][j], sum[i][j-1]) + grid[i][j];
        return sum[m-1][n-1];
    }

    // 优化空间版本
    // https://www.cnblogs.com/grandyang/p/4353255.html
    int minPathSum2(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> cur(n, INT_MAX);

        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == 0) {   // 第一列 只能有上一个格子进行更新
                    dp[j] += grid[i][j];
                } else          //          i-1行     i行;  第一行INT_MAX 被忽略
                    dp[j] = grid[i][j] + min(dp[j], dp[j-1]);
            }
        }
        return dp[n-1];
    }
};

}

int main(int argc, char* argv[]) {
    {
        using namespace so1;
        std::cout << path2(0,0) << std::endl;

        printVector(cache);
    }

    std::cout << so2::Paths_iter() << std::endl;
	return 0;
}
