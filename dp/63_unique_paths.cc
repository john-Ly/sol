#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

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

vector<vector<int>> obstacleGrid = { {0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
int m = obstacleGrid.size(); int n = obstacleGrid[0].size();


namespace so1 {
vector<vector<int>> cache(m+1, vector<int>(n+1, -1));
// 自顶向下dp 递归
// uniquePaths(y, x) = 返回从(y, x)其实到最终目标的子路径的个数
int uniquePathsWithObstacles(int y, int x) {
    int& ret = cache[y][x];
    if(y >= m || x >= n) return ret = 0;
    // 保证y x都在合法的范围
    if(obstacleGrid[y][x] == 1) ret = 0;
    if(y == m-1 && x == n-1) return ret = 1;
    if(ret != -1) return ret;

    return ret = uniquePathsWithObstacles(y, x+1) + uniquePathsWithObstacles(y+1, x);
}
}

// @TODO 迭代动规没有AC
namespace so2 {
// uniquePaths(y, x) = 返回从(y, x)其实到最终目标的子路径的个数
int uniquePaths_iter() {
    // 初始化1 保证(0,x) 和 (y,0) 的下标 路径个数都是确定的 1条
    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = m-1; i >= 0 ; i--) {
        for (int j = n-1; j >= 0; j--) {
            if(obstacleGrid[i][j] == 1) continue;
            else {
                if( (i==m-1 && obstacleGrid[i][j+1] ==0)
                    || (j==n-1 && obstacleGrid[i+1][j] ==0) ) {
                    dp[i][j] = 1;
                } else {
                    //         向下走        向右走
                    dp[i][j] = dp[i+1][j] + dp[i][j+1];
                }
            }
        }
    }

    printVector(dp);
    return dp[0][0];
}

// https://leetcode.com/problems/unique-paths/discuss/22980/Clean-and-simple-DP-java
// 灵感来源与上面的回答
int uniquePaths_iter2() {
    // 初始化1 保证(0,x) 和 (y,0) 的下标 路径个数都是确定的 1条
    vector<vector<int>> dp(2, vector<int>(n, 0));

    for (int i = m-1; i >= 0 ; i--) {
        for (int j = n-1; j >= 0; j--) {
            if(obstacleGrid[i][j] == 1) continue;  // 有障碍直接跳出
            else {
                if( (i==m-1 && obstacleGrid[i][j+1] ==0)
                    || (j==n-1 && obstacleGrid[i+1][j] ==0) ) {
                    dp[i%2][j] = 1;
                } else {
                    dp[i%2][j] = dp[(i+1)%2][j] + dp[i%2][j+1];
                }
            }
        }
    }

    printVector(dp);
    return dp[0][0];
}

// int uniquePaths_iter2(int m, int n) {
//     // 初始化1 保证(0,x) 和 (y,0) 的下标 路径个数都是确定的 1条
//     vector<vector<int>> dp(2, vector<int>(n, 1));

//     for (int i = m-2; i >= 0 ; i--) {
//         for (int j = n-2; j >= 0; j--) {
//             //         向下走        向右走
//         }
//     }

//     // printVector(dp);
//     return dp[0][0];
// }
}

int main() {
    // std::memset(cache, -1, sizeof(cache));
    {
        using namespace so1;
        cout << uniquePathsWithObstacles(0, 0) << endl;
        printVector(cache);
    }

    {
        using namespace so2;
        cout << uniquePaths_iter() << endl;
        cout << uniquePaths_iter2() << endl;
    }

    return 0;
}