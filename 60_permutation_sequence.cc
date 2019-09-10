#include <iostream>
#include <vector>
#include <string>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4358678.html
// 中文博客没有讲清楚问题

// https://leetcode.com/problems/permutation-sequence/discuss/22508/An-iterative-solution-for-reference
/*
The logic is as follows:
 for n numbers the permutations can be divided to (n-1)! groups, for n-1 numbers can be divided to (n-2)! groups, and so on.
 Thus k/(n-1)! indicates the index of current number, and k%(n-1)! denotes remaining index for the remaining n-1 numbers.

 We keep doing this until n reaches 0, then we get n numbers permutations that is kth.
*/

// 有点像页表的索引
// 默认n 是1-9的范围 全排列也就9!
string getPermutation(int n, int k) {
    string res;
    string num = "123456789";
    // 阶乘数组
    vector<int> f(n, 1);
    for (int i = 1; i < n; ++i) f[i] = f[i - 1] * i;
    --k; // 下标从0开始计算

    for (int i = n; i >= 1; --i) {
        int j = k / f[i - 1];
        k %= f[i - 1];
        res.push_back(num[j]);
        num.erase(j, 1); // 全排列不能重复之前的数字 因此要排除
    }
    return res;
}

int main() {
    cout << getPermutation(4, 9) << endl;

    return 0;
}