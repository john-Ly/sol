#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

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

// @TODO 和全排列的思想一致
// https://www.cnblogs.com/grandyang/p/4380706.html
// 其实组成的n*n的n皇后矩阵可以看成一个数学坐标系，我们知道y=k*x+b表示的是一条直线，k为斜率，b为y轴上的高度，当k=0;b=0;的时候y=x为一条穿过坐标系原点并且与x轴成45度的直线。

/*
https://zhangluncong.com/2018/09/22/solveNQueens/
column[j] 表示一条垂j轴的垂直线
cross1[j + i] 表示左低右高斜率45度的直线
cross2[-j + i + n - 1] 表示左高右低斜率45度的直线，-j+i有可能会变成负数，我们数组没有负数的下标，因此我们加上n-1来保证下标不为负数，其实加多少都无所谓，只要我们有一个足够大的数组来保存这条直线上的点。

 */
namespace so1 {
void dfs(int i, vector<bool> &col, vector<bool>& main, vector<bool> &anti, int &count) {
    if (i == col.size()) {
        count++; return;
    }
    for (int j = 0; j < col.size(); j++) {
        // 副对角线: i+j = n-1(常数)
        // 主对角线: j-i+n = n(常数)
        if (col[j] && main[j-i+col.size()] && anti[i+j]) {
            col[j] = main[j-i+col.size()] = anti[i+j] = false;
            dfs(i+1, col, main, anti, count);
            col[j] = main[j-i+col.size()] = anti[i+j] = true;
        }
    }
}

int totalNQueens(int n) {
    // 一列被占用, 所有行都无效
    vector<bool> col(n, true);
    vector<bool> anti(2*n-1, true);
    vector<bool> main(2*n-1, true);
    int count = 0;
    dfs(0, col, main, anti, count);
    return count;
}
}

namespace so2 {
bool isValid(vector<int>& queenCol, int row, int col) {
    for (int i = 0; i < row; ++i) {
        // 不同行的相同列        主/副对角线(行-行; 列-列)(等腰直角三角形 两直角边相等)
        if (col == queenCol[i] || abs(row - i) == abs(col - queenCol[i])) return false;
    }
    return true;
}

void helper(int curRow, vector<int>& queenCol, int& res) {
    int n = queenCol.size();
    if (curRow == n) {
        res++; return;
    }

    for (int i = 0; i < n; ++i) {
        if (isValid(queenCol, curRow, i)) {
            queenCol[curRow] = i;
            helper(curRow + 1, queenCol, res);
            queenCol[curRow] = -1;
        }
    }
}

int solveNQueens(int n) {
    int res = 0;
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

    cout << so2::solveNQueens(8) << endl;
    cout << so1::totalNQueens(8) << endl;

    return 0;
}