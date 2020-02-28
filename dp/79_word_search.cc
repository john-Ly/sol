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

// 在字符矩阵里面 判断单词是否存在(四个方向都可以扩展)
// https://leetcode.com/problems/word-search/discuss/27660/Python-dfs-solution-with-comments.
// 代码即注释 + dfs深度优先
namespace so1 {
    // idx 表示word 前idx字符已经找到
bool search(vector<vector<char>>& board, string word, int idx, int i, int j, vector<vector<bool>>& visited) {
    if (idx == word.size()) return true;
    int m = board.size(), n = board[0].size();
    //                                      同一个字符只能访问一次
    if (i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || board[i][j] != word[idx]) return false;

    // backtracking
    visited[i][j] = true;
    bool res = search(board, word, idx + 1, i - 1, j, visited)
                || search(board, word, idx + 1, i + 1, j, visited)
                || search(board, word, idx + 1, i, j - 1, visited)
                || search(board, word, idx + 1, i, j + 1, visited);
    visited[i][j] = false;
    return res;
}

bool exist(vector<vector<char>>& board, string word) {
    if (board.empty() || board[0].empty()) return false;
    int m = board.size(), n = board[0].size();
    // 记录是否访问过当前节点
    vector<vector<bool>> visited(m, vector<bool>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (search(board, word, 0, i, j, visited)) return true;
        }
    }
    return false;

}
}

// https://www.cnblogs.com/grandyang/p/4332313.html
// DFS+backtracking
namespace so2 {
// idx: 代表当前字符的下标
bool search(vector<vector<char>>& board, string word, int idx, int i, int j) {
    if (idx == word.size()) return true;
    int m = board.size(), n = board[0].size(); // 改成# 统一了两种判断情况
    if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[idx]) return false;
    char c = board[i][j];
    board[i][j] = '#';
    bool res = search(board, word, idx + 1, i - 1, j)
                || search(board, word, idx + 1, i + 1, j)
                || search(board, word, idx + 1, i, j - 1)
                || search(board, word, idx + 1, i, j + 1);
    board[i][j] = c;
    return res;
}

bool exist(vector<vector<char>>& board, string word) {
    if (board.empty() || board[0].empty()) return false;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            if (search(board, word, 0, i, j)) return true;
        }
    }
    return false;
}
}

// 剑指 66
// @NOTE 为什么有些bfs_回溯 需要反转   S[i][j] = "#"  s[i][j] = "c"

// 查找字符串 两种搜索路径可能会有重合 所以要恢复原状
// 探索机器人的路径 根本不需要 因为dfs在一个联通分量内可以找出所有符合要求的点
class Solution {
public:
    int movingCount(vector<vector<T>> const &board, int threshold) {
        int m = board.size(), n = board[0].size(); // 改成# 统一了两种判断情况
        int count = 0;
        if(threshold < 1 || m < 1 || n < 1){ return count; }

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        count = movingCountCore(threshold, rows, cols, 0, 0, visited);
        return count;
    }

private:
    int movingCountCore(int threshold, int rows, int cols, int row, int col,
                        vector<vector<bool>>& visited){
        int count = 0;
        if(row >= 0 && row < rows && col >= 0 && col < cols &&
           getDigitSum(row)+getDigitSum(col) <= threshold &&
           !visited[row*cols+col]) {
            visited[row*cols+col] = true;
            count = 1 + movingCountCore(threshold, rows, cols, row+1, col, visited)
                + movingCountCore(threshold, rows, cols, row-1, col, visited)
                + movingCountCore(threshold, rows, cols, row, col+1, visited)
                + movingCountCore(threshold, rows, cols, row, col-1, visited);
        }
        return count;
    }

    int getDigitSum(int num){
        int sum = 0;
        while(num){
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};

