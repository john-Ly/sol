#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

// https://leetcode.com/problems/unique-paths/discuss/22954/C%2B%2B-DP
//  从 空间复杂度逐步分析

//https://leetcode.com/problems/unique-paths/discuss/22958/Math-solution-O(1)-space
// 实际是一个组合问题 A(m+n, m+n) @TODO
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