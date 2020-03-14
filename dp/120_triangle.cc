#include <iostream>
#include <vector>

// unique_path + house_robber + triangle + lis
// @TODO house robber问题 动态规划题型有一类(先求出最优化解 然后求出最优解的个数 ==> 最难的是打印出每个最优解)

// P158 算法书
int cache[Size][Size];
int path2(int y, int x) {
    int& ret = cache[y][x];
    // 制表要完整 否则count()利用不了
	if(y == Size-1) return ret = triangle[y][x];

	if(ret != -1) return ret;

	return ret = MAX(path2(y+1, x+1), path2(y+1, x)) + triangle[y][x];
}


// path(x, y, sum) = 当前位置为(y, x) 路径中所有数值的总和为sum时, 返回当前路径延伸到最后一行时的最小值
// path 返回的是沿着x, y并且此时已解自问题的结果为sum的时, 到最后一行 整体的最小值

// 但是sum为何值时, 并不影响后续的结果(求最小的路径)

// path2(y, x) = 返回从(y, x)起始到最后一行的子路径(剩余子问题)总和的最小值
// 可能的路径个数和 三角形的行数 正相关(行数加1, 个数就会增加1倍)   n行三角形 == 2^ n-1
// time: O(2^ n)  @TODO P148 求解二项式系数的问题 时间复杂度 子问题的个数是 O(n^2)(还有杨辉三角)
//////////////////////////////////////////////////////////////////////////////////////////////////////


// https://leetcode.com/problems/triangle/discuss/38730/DP-Solution-for-Triangle
// 解释非常棒 重复自问题 + 最优子结构
// 这个分析比较好的地方是 bottom-up/top-down 两个流派进行DP
// top-down 往往需要额外的数组 因此空间换时间   但是整个过程的拆解比较trick 需要思考
// bottom-up 比较直观 直接更新dp数组即可

// k表示棋盘的层数 k [n-2, 1]  --> k+1 == n-1
// minpath[k][i] = min( minpath[k+1][i], minpath[k+1][i+1]) + triangle[k][i];
//
// 进一步优化:
// minpath[i] = min( minpath[i], minpath[i+1]) + triangle[k][i];
class Sol {
public:
// 最后一行 直接就是 最短路径
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    // 复制三角形最后一行
    vector<int> minlen(triangle.back());
    for (int layer=n-2; layer>=0; layer--) { // For each layer
        for (int i=0; i<=layer; i++) { // Check its every 'node'   layer+1 = #node
            // 层数倒序 来更新
            // Find the lesser of its two children, and sum the current value in the triangle with it.
            minlen[i] = min(minlen[i], minlen[i+1]) + triangle[layer][i];
        }
    }
    return minlen[0];
}
};
