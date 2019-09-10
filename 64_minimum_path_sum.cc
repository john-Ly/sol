#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

// 他们的思路都是从 0,0开始(按照题目的思路)
// https://www.cnblogs.com/grandyang/p/4353255.html

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

namespace so2 {
// @TODO 这种题目主要目标好像是优化空间 但是还不会
// https://leetcode.com/problems/minimum-path-sum/discuss/23457/C%2B%2B-DP
int Paths_iter() {
    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[m-1][n-1] = grid[m-1][n-1];
    for (int i = m-2; i >= 0; i--)
        dp[i][n-1] = dp[i+1][n-1] + grid[i][n-1];
    for (int j = n-2; j >= 0; j--)
        dp[m-1][j] = dp[m-1][j+1] + grid[m-1][j];
    // printVector(dp);

    for (int i = m-2; i >= 0 ; i--) {
        for (int j = n-2; j >= 0; j--) {
            dp[i][j] = min(dp[i+1][j], dp[i][j+1]) + grid[i][j];
        }
    }

    printVector(dp);
    return dp[0][0];
}

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

