#include <vector>
#include <iostream>
using namespace std;

// 找出孤岛(周围被水包围的岛群)   --> 图的连通性( 二维矩阵可以保证所有的点都被visit, dfs进入几次保证找出孤岛)
// @TODO bfs也可以解决题目 但是主要应用于 最短路径
class sol_dfs {
public:
int numIslands(vector<vector<short>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int m = grid.size(), n = grid[0].size(), res = 0;
    // 访问数组
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0 || visited[i][j]) continue;
            helper(grid, visited, i, j);
            ++res;
        }
    }
    return res;
}

void helper(vector<vector<short>>& grid, vector<vector<bool>>& visited, int x, int y) {
    // x的合理范围  [0, m-1]
    if (x < 0 || x >= grid.size() ||
        y < 0 || y >= grid[0].size() ||
        grid[x][y] == 0 || visited[x][y]) return;

    visited[x][y] = true; // 找出上下左右相邻位置的岛
    helper(grid, visited, x - 1, y);
    helper(grid, visited, x + 1, y);
    helper(grid, visited, x, y - 1);
    helper(grid, visited, x, y + 1);
}

};

class sol_dfs_erase_one {
public:
int numIslands(vector<vector<short>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int m = grid.size(), n = grid[0].size(), res = 0;
    // 访问数组
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                eraseIslands(grid, i, j);
                ++res;
            }
        }
    }
    return res;
}

void eraseIslands(vector<vector<short>>& grid, int x, int y) {
    // x的合理范围  [0, m-1]
    if (x < 0 || x >= grid.size() ||
        y < 0 || y >= grid[0].size() ||
        grid[x][y] == 0) return;

    grid[x][y] = 0; // 找出上下左右相邻位置的岛
    eraseIslands(grid, x - 1, y);
    eraseIslands(grid, x + 1, y);
    eraseIslands(grid, x, y - 1);
    eraseIslands(grid, x, y + 1);
}

};


int main() {
    vector<vector<short>> grid {{1,1,0,0,0},
                               {1,1,0,0,0},
                               {0,0,1,0,0},
                               {0,0,0,1,1}};
    sol_dfs_erase_one so1;
    cout << so1.numIslands(grid) << '\n';

    return 0;
}