#include <vector>
#include <iostream>
using namespace std;

// https://leetcode.com/problems/surrounded-regions/discuss/41646/concise-12ms-c-dfs-solution/39912
// https://www.cnblogs.com/grandyang/p/4555831.html
// DFS的解法 不是很理解
class Solution {
public:
    void solve(vector<vector<short>>& grid) {
        if (grid.empty() || grid[0].empty()) return;
        int row = grid.size(), col = grid[0].size();

        // 1. 检查四条边界 将边界上的 '0' 全部转化为占位符
        for (int i = 0; i < row; ++i) {
            check(grid, i, 0);             // first column
            check(grid, i, col - 1);       // last column
        }
        // 因为四个角 都被双重检查
        for (int j = 1; j < col - 1; ++j) {
            check(grid, 0, j);             // first row
            check(grid, row - 1, j);       // last row
        }

        for (int i = 0; i < rwo; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] == 0) grid[i][j] = 1;
                else if (grid[i][j] == 2) grid[i][j] = 0;
            }
        }
    }

    // 棋盘的四个角落 实际对于解题没有意义
    void check(vector<vector<short>>& grid, int i, int j) {
        if (grid[i][j] == O) {
            grid[i][j] = 2;
            if (i > 1) check(grid, i - 1, j); // 上
            if (j > 1) check(grid, i, j - 1); // 左
            if (i + 1 < grid.size()) check(grid, i + 1, j); // 下
            if (j + 1 < grid[0].size()) check(grid, i, j + 1); // 右
        }
    }

};

// BFS 才是最简便的想法
// https://leetcode.com/problems/surrounded-regions/discuss/41649/My-BFS-solution-(C++-28ms)/39921
// https://leetcode.com/problems/surrounded-regions/discuss/41649/My-BFS-solution-(C%2B%2B-28ms)
class Solution_BFS {
public:
    void solve(vector<vector<short>>& grid) {
        if (grid.empty() || grid[0].empty()) return;
        int row = grid.size(), col = grid[0].size();

        // 1. 检查四条边界 将边界上的 '0' 全部转化为占位符
        for (int i = 0; i < row; ++i) {
            if (grid[i][0] == 0)
                check(grid, i, 0);             // first column
            if (grid[i][col-1] == 0)
                check(grid, i, col - 1);       // last column
        }

        // 因为四个角 都被双重检查
        for (int j = 1; j < col - 1; ++j) {
            if (grid[0][j] == 0)
                check(grid, 0, j);             // first row
            if (grid[row-1][j] == 0)
                check(grid, row - 1, j);       // last row
        }

        for (int i = 0; i < rwo; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] == 0) grid[i][j] = 1;
                else if (grid[i][j] == 2) grid[i][j] = 0;
            }
        }
    }

    // 棋盘的四个角落 实际对于解题没有意义
    void check(vector<vector<short>>& grid, int i, int j) {
        int row = grid.size(), col = grid[0].size();
        queue<pair<int, int> > q;
        q.push(make_pair(i, j));
        while (!q.empty()) {
            pair<int, int> elem = q.front(); q.pop();
            i = elem.first; j = elem.second;
            if (i >= 0 && i < row && j >= 0 && j < col && grid[i][j] == 0) {
                grid[i][j] = 2;
                q.push(make_pair(i-1, j));
                q.push(make_pair(i+1, j));
                q.push(make_pair(i, j-1));
                q.push(make_pair(i, j+1));
            }
        }
    }

};

int main() {
    vector<vector<short>> grid {{1,1,1,1},
                                {1,0,0,1},
                                {1,1,0,1},
                                {1,0,1,1}};
    sol so1;
    cout << so1.solve(grid) << '\n';

    return 0;
}