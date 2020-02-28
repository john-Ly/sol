#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// https://www.cnblogs.com/grandyang/p/4550604.html
// 暴搜才是最直观的思路
bool allOnes(vector<vector<char>>& matrix, int row, int col, int n){
    for(int i=row; i <= row+n; i++){
        for(int j=col; j <= col+n; j++){
            if(i >= matrix.size() || j >= matrix[0].size()) return false;
            if(matrix[i][j]-'1'!=0) return false;
        }
    }
    return true;
}

int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.size() <= 0 || matrix[0].size() <= 0) return 0;
    int res = 0;
    int m = matrix.size(); // row_len
    int n = matrix[0].size();  // col_len
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            int h = 0;
            // 计算正方形的长度
            while(allOnes(matrix,i,j,h)) {
                h++;
            }

            res = max(res,h);
        }
    }
    return res*res;
}
