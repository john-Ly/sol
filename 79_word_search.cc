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

// https://leetcode.com/problems/word-search/discuss/27660/Python-dfs-solution-with-comments.
// 代码即注释
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
bool exist(vector<vector<char>>& board, string word) {
    if (board.empty() || board[0].empty()) return false;
    int m = board.size(), n = board[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (search(board, word, 0, i, j)) return true;
        }
    }
    return false;
}
bool search(vector<vector<char>>& board, string word, int idx, int i, int j) {
    if (idx == word.size()) return true;
    int m = board.size(), n = board[0].size();
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
}