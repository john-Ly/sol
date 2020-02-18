#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iterator>
using namespace std;

// @TODO
// https://www.cnblogs.com/grandyang/p/5727892.html

// 详细介绍了各种算法
// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/301357/Java-0ms-(added-Python-and-C%2B%2B)%3A-Easy-to-understand-solutions-using-Heap-and-Binary-Search

// 1. 在行列有序的 方阵 n*n 找出第k小
// 相当于多个有序链表归并排序
int kthSmallest(vector<vector<int>>& matrix, int k) {
    // 维护最大堆 (每次容量吵了, 排除最大的)
    priority_queue<int> q;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            q.push(matrix[i][j]);
            if (q.size() > k) q.pop();
        }
    }

    return q.top();
}

// 也可以使用二分法 但是有点复杂






