#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4322653.html
// 单调栈的思想很巧妙 (和dp的方法思路差不多 递增栈 找到左起第一个小于当前的数字)
// https://www.cnblogs.com/grandyang/p/8887985.html

// https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/28902/5ms-O(n)-Java-solution-explained-(beats-96)
// 动态规划算法
// @NOTE 关键是如何找出lessFrom  范围的边界要确定
int largestRectangleArea(vector<int>& heights) {
    int size = heights.size();
    if(size == 0) return 0;

    // 左边第一个小于cur的下标
    int lessFromLeft[size]; lessFromLeft[0] = -1;
    // 右边第一个小于cur的下标
    int lessFromRight[size]; lessFromRight[size - 1] = size;

    for (int i = 1; i < size; i++) {
        int p = i - 1;

        // 目前是要找到 i到 lessFromLeft[i] 之间都是 >= height[i]
        // height[p/i-1] >= height[i] ==> lessFromLeft[p]代表的座标 还是在上述范围之间
        while (p >= 0 && heights[p] >= heights[i]) {
            p = lessFromLeft[p]; // 所以可以利用之前下标计算的结果
        }
        lessFromLeft[i] = p;
    }

    for (int i = size-2; i >= 0; i--) {
        int p = i + 1;

        while (p < size && heights[p] >= heights[i]) {
            p = lessFromRight[p];
        }
        lessFromRight[i] = p;
    }

    int maxArea = 0;
    for (int i = 0; i < size; i++) {
        // {
        //   auto tmp = heights[i] * (lessFromRight[i] - lessFromLeft[i] - 1);
        //   if(tmp == 10 && i==3) cout << lessFromRight[i] << "-" << lessFromLeft[i] << endl;
        // }
        maxArea = max(maxArea, heights[i] * (lessFromRight[i] - lessFromLeft[i] - 1));
    }

    return maxArea;
}

// 找到局部峰值来做
int largestRectangleArea2(vector<int> &height) {
    int res = 0;
    for (int i = 0; i < height.size(); ++i) {
        if (i + 1 < height.size() && height[i] <= height[i + 1]) {
            continue;
        }
        // 找到局部峰值(i)后 向左边遍历
        int minH = height[i];
        for (int j = i; j >= 0; --j) {
            minH = min(minH, height[j]);
            int area = minH * (i - j + 1);
            res = max(res, area);
        }
    }
    return res;
}

//还是像局部峰值的处理
// @NOTE 单调递增栈: 方便找到左边起比当前元素的小的 第一个数
// 单调栈里面存放座标
int largestRectangleArea3(vector<int> &height) {
    int res = 0;
    stack<int> st; // 单调递增栈
    // 在高度数组最后面加上一个0，这样原先的最后一个板子也可以被处理了
    height.push_back(0);
    for (int i = 0; i < height.size(); ++i) {
        if (st.empty() || height[st.top()] < height[i]) {
            st.push(i);
            // cout << height[i] << "-" << i  << endl;
        } else {
            // 栈顶元素 大于等于 height[i]
            int cur = st.top(); st.pop();
            // cout << height[cur] << " " << i << endl;
            // 如果st.pop后 栈空, 说明cur左边范围里 cur是最短的板子, 直接i为宽度
            // height[i-1] = cur , i 代表[0, i-1]
            res = max(res, height[cur] * (st.empty() ? i : (i - st.top() - 1)));
            --i; // @NOTE 执行完循环体 i会++, 但是栈顶元素需要继续判断, 因此先--
        }
    }
    return res;
}

namespace so1 {
// 一个元素只会进栈和出栈一次 因此O(n) 平摊时间复杂度
    // 局部峰值 实际就是 单调递增栈(栈顶-极高值)
int largestRectangleArea(vector<int>& heights) {
    int res = 0;
    stack<int> st;
    heights.push_back(0);
    for (int i = 0; i < heights.size(); ++i) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            int cur = st.top(); st.pop();
            res = max(res, heights[cur] * (st.empty() ? i : (i - st.top() - 1)));
        }
        st.push(i);
    }
    return res;
}
}

int main() {
    vector<int> v = {2,1,5,6,2,3};
    cout << largestRectangleArea3(v) << endl;
    cout << largestRectangleArea(v) << endl;
    cout << so1::largestRectangleArea(v) << endl;

    return 0;
}