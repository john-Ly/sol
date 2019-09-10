#include <vector>
#include <iostream>
using namespace std;

bool isValidSudoku(vector<vector<char>>& board) {
    // https://leetcode.com/problems/valid-sudoku/discuss/15464/My-short-solution-by-C%2B%2B.-O(n2)
    int row[9][9] = {0}, col[9][9] = {0}, cell[9][9] = {0};

    // sudoku 通常是9*9
    /*  系数 k = f(i, j) = (i/3)*3 + j/3  可以选出每一个cell的下标
        0  0  0 | 1  1  1 | 2  2  2
        0  0  0 | 1  1  1 | 2  2  2
        0  0  0 | 1  1  1 | 2  2  2
        --------+---------+---------
        3  3  3 | 4  4  4 | 5  5  5
        3  3  3 | 4  4  4 | 5  5  5
        3  3  3 | 4  4  4 | 5  5  5
        --------+----------+--------
        6  6  6 | 7  7  7 | 8  8  8
        6  6  6 | 7  7  7 | 8  8  8
        6  6  6 | 7  7  7 | 8  8  8
    */

    for(int i = 0; i < board.size(); ++ i)
        for(int j = 0; j < board[i].size(); ++ j)
            if(board[i][j] != '.') {
                // num 因为1-9 但是棋盘下标是0-8
                // [下标(row/col/cell)][对应的数字]
                int num = board[i][j] - '0' - 1, k = i / 3 * 3 + j / 3;
                // 先判断行 -> 列 -> cell
                if(row[i][num] || col[j][num] || cell[k][num])
                    return false;
                row[i][num] = col[j][num] = cell[k][num] = 1;
            }

    return true;
}


int main() {

    return 0;
}