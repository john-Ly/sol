#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/container-with-most-water/solution/
// https://www.cnblogs.com/grandyang/p/4455109.html

// 二维数组类似全排列
//  {1,8,6,2,5,4,8,3,7};
//     |             |
// 虽然下标是 1-8,但是其实间隙的数目 也就是7(8-1)

int maxArea(vector<int>& height) {
    int maxarea = 0;
    for (int i = 0; i < height.size(); i++) {
        for (int j = i + 1; j < height.size(); j++) {
            maxarea = max(maxarea, min(height[i], height[j]) * (j - i));
            {
                cout << "height[i-j]: " << height[i] << " " << height[j] << endl;;
                cout << "[j-i]: " << j << " " << i << endl;
                cout << "=======" << endl;
            }
        }
    }

    return maxarea;
}

// 矩形的面积不仅 长度影响  宽度也影响
int maxArea2(vector<int>& height) {
    int res = 0, i = 0, j = height.size() - 1;
    while (i < j) {
        res = max(res, min(height[i], height[j]) * (j - i));
        // 移动最小的 因为短板效应
        // 如果移动大的, 面积其实还是受限与小的, 所以还不如移动大的
        height[i] < height[j] ? ++i : --j;
    }
    return res;
}

int main() {
    vector<int> v = {1,8,6,2,5,4,8,3,7};
    cout << maxArea(v) << endl;
    cout << maxArea2(v) << endl;

    return 0;
}