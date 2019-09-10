// 面试题4：二维数组中的查找
// 题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按
// 照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个
// 整数，判断数组中是否含有该整数。

// https://stackoverflow.com/questions/2457792/how-do-i-search-for-a-number-in-a-2d-array-sorted-left-to-right-and-top-to-botto
// @NOTE 有详细的解释
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4323301.html
// https://www.cnblogs.com/grandyang/p/4669134.html
// leetcode 74_240  题目不一样(一个可以看成一维数组 另一个行列均递增) 前者范围更大

// 可以把题目考虑成 1d的有序数组
bool searchMatrix(vector<vector<int> > &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    if (target < matrix[0][0] || target > matrix.back().back()) return false;
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    // 把一个长度为n的一维数组转化为m*n的二维数组(m*n = n)后，那么原一维数组中下标为i的元素将出现在二维数组中的[i/n][i%n]的位置
    while (left <= right) {
        int mid = (left + right) / 2;
        if (matrix[mid / n][mid % n] == target) return true;
        else if (matrix[mid / n][mid % n] < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

bool searchMatrix(vector<vector<int> > &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int m = matrix.size(), n = matrix[0].size();
    int row = 0, column = n - 1;
    // 右上角开始进行检索
    while (row < m && column >= 0) {
        if (matrix[row][column] == target) {
            return true;
        } else if (matrix[row][column] > target) --column;
        else ++row;
    }
    return false;
}

bool Find(int* matrix, int rows, int columns, int number) {
    bool found = false;
    if(matrix != nullptr && rows > 0 && columns > 0) {
        int row = 0;
        int column = columns - 1;
        while(row < rows && column >=0) {
            if(matrix[row * columns + column] == number) {
            }
            else if(matrix[row * columns + column] > number)
                -- column;
            else
                ++ row;
        }
    }

    return found;
}

// ====================测试代码====================
void Test(char* testName, int* matrix, int rows, int columns, int number, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    bool result = Find(matrix, rows, columns, number);
    if(result == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数在数组中
void Test1()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test1", (int*)matrix, 4, 4, 7, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数不在数组中
void Test2()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test2", (int*)matrix, 4, 4, 5, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最小的数字
void Test3()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test3", (int*)matrix, 4, 4, 1, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最大的数字
void Test4()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test4", (int*)matrix, 4, 4, 15, true);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最小的数字还小
void Test5()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test5", (int*)matrix, 4, 4, 0, false);
}

//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最大的数字还大
void Test6()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    Test("Test6", (int*)matrix, 4, 4, 16, false);
}

// 鲁棒性测试，输入空指针
void Test7()
{
    Test("Test7", nullptr, 0, 0, 16, false);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}

