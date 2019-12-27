#include <vector>
// 杨辉三角的5个性质o
// 杨辉三角形第n层（顶层称第0层，第1行，第n层即第 n+1 行，此处n为包含0在内的自然数）
//  正好对应于二项式 (a+b)^n
// 1. 第n层 有n个数字
// 2. 每层数字左右对称 1 3 3 1
// 3. 第n行第k个数字等于第 n-1 行的第 k-1 个数字与第k个数字的和  (有点类似三角形路径和, 只能向左和右走)

// 给出行数, 输出所有行的结果
// Input: 5
// Output:
// [
//      [1],
//     [1,1],
//    [1,2,1],
//   [1,3,3,1],
//  [1,4,6,4,1]
// ]
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows, vector<int>());
        for (int i = 0; i < numRows; ++i) { // i: [0,4]
            res[i].resize(i + 1, 1);
            // i=2 代表从第3行开始 更新整个数组
            for (int j = 1; j < i; ++j) {
                // 利用性质3
                res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
            }
        }
        return res;
    }
};

// 求组合数 导致int型整数溢出
class Solution_one_row {
public:
    // Cnk:
    // 1 3 3 3 ==> C30  C31  C32  C33
    vector<int> getRow(int rowIndex) {
        vector<int> out;
        if (rowIndex < 0) return out;
        for (int i = 0; i <= rowIndex; ++i) {
            if ( i == 0 || i == rowIndex) out.push_back(1);
            else out.push_back (computeCnk(rowIndex, i));
        }
        return out;
    }

    int computeCnk(int n, int k) {
        if (k > n) return 0;
        if (k > n/2) k = n - k;
        int numerator = 1, denominator = 1;
        //   n * n-1 * ... * n-k
        //  ---------------------
        //   k * k-1 * ... * 1
        for (int i = 0; i < k; ++i) {
            numerator *= n - i;
            denominator *= k - i;
        }
        if (denominator != 0) return numerator/denominator;
        return 0;
    }
};


// https://www.cnblogs.com/grandyang/p/4031536.html
class Solution_dp {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex+1);
        res[0] = 1;
        // 这里就是dp的优化
        for (int i = 1; i <= rowIndex; ++i) {
            // 很巧妙
            // res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
            // 先计算出了i-1行  j-1 j 都知道
            // 计算 i行时  a[j] 还是i-1行的值   所以 a[j] += a[j-1]  就是i行 j列的值
            for (int j = 1; j >= 1; --j) {
                res[j] += res[j-1];
            }
        }
        return res;
    }
};