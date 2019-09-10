#include <vector>
#include <iostream>
using namespace std;


// https://www.cnblogs.com/grandyang/p/4421852.html

// @TODO 无法理解 j=9后 i 怎么更新
bool isValid(vector<vector<char> > &board, int i, int j) {
    for (int col = 0; col < 9; ++col) {
        if (col != j && board[i][j] == board[i][col]) return false;
    }
    for (int row = 0; row < 9; ++row) {
        if (row != i && board[i][j] == board[row][j]) return false;
    }

    //  0-2 => 0; 3-5 => 1; 6-8 => 2
    for (int row = i / 3 * 3; row < i / 3 * 3 + 3; ++row) {
        for (int col = j / 3 * 3; col < j / 3 * 3 + 3; ++col) {
            if ((row != i || col != j) && board[i][j] == board[row][col]) return false;
        }
    }

    return true;
}

bool solveSudokuDFS(vector<vector<char> > &board, int i, int j) {
    if (i == 9) return true;
    if (j >= 9) return solveSudokuDFS(board, i + 1, 0);
    if (board[i][j] == '.') {
        for (int k = 1; k <= 9; ++k) {
            board[i][j] = (char)(k + '0');
            if (isValid(board, i , j)) {
                if (solveSudokuDFS(board, i, j + 1)) return true;
            }
            board[i][j] = '.';
        }
    } else {
        return solveSudokuDFS(board, i, j + 1);
    }
    return false;
}

void solveSudoku(vector<vector<char> > &board) {
    cout << solveSudokuDFS(board, 0, 0) << endl;
}

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
    vector<vector<char> > board { {"5","3",".",".","7",".",".",".","."},
                                  {"6",".",".","1","9","5",".",".","."},
                                  {".","9","8",".",".",".",".","6","."},
                                  {"8",".",".",".","6",".",".",".","3"},
                                  {"4",".",".","8",".","3",".",".","1"},
                                  {"7",".",".",".","2",".",".",".","6"},
                                  {".","6",".",".",".",".","2","8","."},
                                  {".",".",".","4","1","9",".",".","5"},
                                  {".",".",".",".","8",".",".","7","9"} };
    solveSudoku(board);

    return 0;
}