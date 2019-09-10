#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4377782.html
// https://segmentfault.com/a/1190000003733325

template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{\n";
	for (vector<T> row: mat) {
        cout << "  [";
		for (T val: row) {
			cout << val << ',';
		}
        cout << "],\n";
	}
    cout << "}\n";
}

namespace so1 {
// 如何用 C++ 在 10 行内写出八皇后？ - 赵一勤的回答 - 知乎
// https://www.zhihu.com/question/28543312/answer/286586930
const int N = 8;
vector<int> queen(N);
vector<vector<int>> res;

bool check(int n) {
  for (int i = 0; i < n; i++) {
    int x = n - i;
    int y = queen[n] - queen[i];

    if (y == 0 || abs(x) == abs(y)) return false;
  }
  return true;
}

void dfs(int n) {
  if (n == N) {
      res.push_back(queen);
  }

  for (int i = 0; i < N; i++) {
    queen[n] = i;
    if (check(n))
      dfs(n + 1);
  }
}

}

namespace so2 {
// 当前行和列的座标
bool isValid(vector<string>& queens, int row, int col) {
    // 之前行的相同列是否有放置
    for (int i = 0; i < row; ++i) {
        if (queens[i][col] == 'Q') return false;
    }
    // 主 对角线
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (queens[i][j] == 'Q') return false;
    }
    // 副 对角线
    for (int i = row - 1, j = col + 1; i >= 0 && j < queens.size(); --i, ++j) {
        if (queens[i][j] == 'Q') return false;
    }
    return true;
}

// curRow: 递归调用到某一行
void helper(int curRow, vector<string>& queens, vector<vector<string>>& res) {
    int n = queens.size();
    if (curRow == n) {
        res.push_back(queens);
        return;
    }
    for (int i = 0; i < n; ++i) {
        // 遍历检查curRow行的 所有列 检查是否可以放置
        if (isValid(queens, curRow, i)) {
            queens[curRow][i] = 'Q';
            helper(curRow + 1, queens, res);
            queens[curRow][i] = '.'; // 因为其他列也可以进行放置
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> queens(n, string(n, '.')); // 棋盘
    helper(0, queens, res);
    return res;
}
}

namespace so3 {
bool isValid(vector<int>& queenCol, int row, int col) {
    for (int i = 0; i < row; ++i) {
        // 不同行的相同列        主/副对角线(行-行; 列-列)(等腰直角三角形 两直角边相等)
        if (col == queenCol[i] || abs(row - i) == abs(col - queenCol[i])) return false;
    }
    return true;
}

void helper(int curRow, vector<int>& queenCol, vector<vector<string>>& res) {
    int n = queenCol.size();
    if (curRow == n) {
        vector<string> out(n, string(n, '.'));
        for (int i = 0; i < n; ++i) {
            out[i][queenCol[i]] = 'Q';
        }
        res.push_back(out);
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (isValid(queenCol, curRow, i)) {
            queenCol[curRow] = i;
            helper(curRow + 1, queenCol, res);
            queenCol[curRow] = -1;
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<int> queenCol(n, -1); // 第i个皇后坐标 (i, queenCol[i]) 直接存放列的index
    helper(0, queenCol, res);
    return res;
}
}

int main() {
    // so1::dfs(0);

    // auto boards = so2::solveNQueens(4);
    // for(auto& v: boards) {
    //     for(auto& s: v) {
    //         cout << s << endl;
    //     }
    //     cout << "==================" << endl;
    // }

    auto boards = so3::solveNQueens(4);
    for(auto& v: boards) {
        for(auto& s: v) {
            cout << s << endl;
        }
        cout << "==================" << endl;
    }
    return 0;
}