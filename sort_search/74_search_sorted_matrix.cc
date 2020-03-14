#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// https://stackoverflow.com/questions/2457792/how-do-i-search-for-a-number-in-a-2d-array-sorted-left-to-right-and-top-to-botto
// @NOTE 有详细的解释

// https://www.cnblogs.com/grandyang/p/4323301.html
// https://www.cnblogs.com/grandyang/p/4669134.html
// leetcode 74_240  题目不一样(一个可以看成一维数组 另一个行列均递增) 前者范围更大

// 把一个长度为n的一维数组转化为m*n的二维数组(m*n = n)后，那么原一维数组中下标为i的元素将出现在二维数组中的[i/n][i%n]的位置
bool searchMatrix_1d(vector<vector<int> > &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    if (target < matrix[0][0] || target > matrix.back().back()) return false;
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (matrix[mid / n][mid % n] == target) return true;
        else if (matrix[mid/n][mid%n] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

// 右上角开始进行检索
bool searchMatrix_2(vector<vector<int> > &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int m = matrix.size(), n = matrix[0].size();
    int row = 0, column = n - 1;
    while (row < m && column >= 0) {
        if (matrix[row][column] == target) {
            return true;
        } else if (matrix[row][column] > target) --column;
        else ++row;
    }
    return false;
}