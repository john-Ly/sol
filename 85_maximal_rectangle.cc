#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/maximal-rectangle/discuss/29064/A-O(n2)-solution-based-on-Largest-Rectangle-in-Histogram
namespace so1 {
// 思路: 从第一行开始 计算出res1
// 从第二行开始(累积第一行的高度数组)  计算出res2
// 同心圆的方式 进行直方图的算法
int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.size() <= 0 || matrix[0].size() <= 0) return 0;

    int m = matrix.size(); // row_len
    int n = matrix[0].size();  // col_len
    int h = 0, w = 0, ret = 0;

    // https://www.cnblogs.com/grandyang/p/4322667.html
    // 只有当前位置小于等于前一个位置的高度的时候，才会去计算矩形的面积
    // 假如最后一个位置的高度是最高的，那么我们就没法去计算并更新结果 res 了，所以要在最后再加一个高度0，这样就一定可以计算前面的矩形面积了
    vector<int> height(n+1, 0);

    for (int i = 0; i < m; ++i) {
        // 对每一行 应用直方图中最大矩形面积的算法
        stack<int> s;
        for (int j = 0; j < n+1; ++j) {
            // set value
            if (j < n) {
                if (matrix[i][j] == '1') height[j] += 1;
                else height[j] = 0;
            }

            // compute area
            while (!s.empty() && height[s.top()] >= height[j]) {
                h = height[s.top()]; s.pop();
                w = s.empty() ? j : j - s.top() - 1;
                ret = max(ret, h*w);
            }

            s.push(j);
        }
    }

    return ret;
}
}

// 可以使用递归 但是太难想到 @TODO
namespace so2 {
// 思路: 同心圆的方式 一定可以利用递归
int maximalRectangle(vector<vector<char>>& matrix) {
    return 0;
}


}

int main() {
    // 二维数组初始化
    // @TODO 二维char如何快速初始化
    vector<vector<char>> v = { {"1","0","1","0","0"} };
    // vector<char> v1 =;
    // v.emplace_back(std::move(v1));
    // v.push_back({"1","0","1","1","1"});
    // v.push_back({"1","1","1","1","1"});
    // v.push_back({"1","0","0","1","0"});

    cout << so1::maximalRectangle(v) << endl;
    return 0;
}