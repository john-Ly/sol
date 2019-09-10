#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4341590.html

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

// 主要使用hash记录
// @TODO 是否允许重复 + 重复设置0 (可能该项已经为0)
void setZeroes2(vector<vector<int>>& matrix) {
    unordered_set<int> row, col;

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            if(matrix[i][j] == 0) {
                row.insert(i);
                col.insert(j);
            }}}

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            if(row.count(i) || col.count(j)) {
                matrix[i][j] = 0;
            }}}
}

// space O(1)
void setZeroes(vector<vector<int>>& matrix) {
    bool row = false, col = false;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            if(matrix[i][j] == 0) {
                if(i == 0) row = true;
                // 因为mat[0][0] 表示行或列均可
                // 比如(2, 0)为0 应该设置(0列) 如果直接设置(0, 0)表示信息不对
                if(j == 0) col = true;
                matrix[0][j] = matrix[i][0] = 0;
            }
        }
    }

    for(int i = 1; i < matrix.size(); i++){
        for(int j = 1; j < matrix[0].size(); j++){
            if(matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
        }
    }

    if(col){
        for(int i = 0; i < matrix.size(); i++) matrix[i][0] = 0;
    }
    if(row){
        for(int j = 0; j < matrix[0].size(); j++) matrix[0][j] = 0;
    }
}

int main() {
    vector<vector<int> > mat = {{0, 1, 2, 0},
                              {3, 4, 5, 2},
                              {1, 3, 1, 5}};

    printVector(mat);
    setZeroes2(mat);
    printVector(mat);

    return 0;
}