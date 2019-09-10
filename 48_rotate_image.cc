#include <iostream>
#include <algorithm>
#include <vector>
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

// 矩阵对称 主要判断 a[i][j] == a[j][i]即可
// 矩阵转置(上三角 i<=j swap即可)

// https://leetcode.com/problems/rotate-image/discuss/18872/A-common-method-to-rotate-the-image
/*
 * clockwise rotate
 * first reverse up to down, then swap the symmetry
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
*/
void rotate(vector<vector<int> > &matrix) {
    // matrix的第一维 进行reverse操作
    reverse(matrix.begin(), matrix.end());

    // 该步 实际为转置操作
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < i; ++j) // 针对下三角进行 交换 因为对称
            swap(matrix[i][j], matrix[j][i]);
    }
}

// https://www.cnblogs.com/grandyang/p/4389572.html
void rotate2(vector<vector<int> > &matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

/*
 * anticlockwise rotate
 * first reverse left to right, then swap the symmetry
 * 1 2 3     3 2 1     3 6 9
 * 4 5 6  => 6 5 4  => 2 5 8
 * 7 8 9     9 8 7     1 4 7
*/
void anti_rotate(vector<vector<int> > &matrix) {
    for (auto vi : matrix) reverse(vi.begin(), vi.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < i; ++j) // 针对下三角进行 交换 因为对称
            swap(matrix[i][j], matrix[j][i]);
    }
}

int main() {
    vector<vector<int> > v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    printVector(v);
    // reverse(v.begin(), v.end());
    // printVector(v);
    // rotate(v);
    rotate2(v);
    printVector(v);
    anti_rotate(v);
    printVector(v);
    anti_rotate(v);
    printVector(v);

    return 0;
}