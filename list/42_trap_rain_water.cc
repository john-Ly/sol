#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 两边高，中间低, 才能装水
// 单调递减栈(栈顶存放 极低值) 一旦发现当前的数字大于栈顶元素了，那么就有可能会有能装水的地方产生。
// https://www.cnblogs.com/grandyang/p/8887985.html
namespace so1 {
int trap(vector<int>& height) {
    int ans = 0, current = 0;
    stack<int> st;
    while (current < height.size()) {
        while (!st.empty() && height[current] > height[st.top()]) {
            /*
             递减栈里至少有一个高度
             1. 如果只有一个的话，那么不能形成坑，直接跳过
             2. 如果多于一个的话，那么此时把栈顶元素取出来当作坑，新的栈顶元素就是左边界，当前高度是右边界，只要取二者较小的，减去坑的高度，，二者相乘就是盛水量啦
             */
            int bottom = st.top(); st.pop();
            if (st.empty()) break;

            // 长度(两个柱子的间隙)就是右边界坐标减去左边界坐标再减1
            int distance = current - st.top() - 1;
            // 左/右边界较高的 减去 坑的高度即可
            int bounded_height = min(height[current], height[st.top()]) - height[bottom];
            ans += distance * bounded_height;
        }
        // 栈为空 或者 当前高度 <= 栈顶, 压入座标值(方便计算水平距离)
        st.push(current++);
    }
    return ans;
}
}

// https://leetcode.com/problems/trapping-rain-water/solution/
// 双指针
// 具体参考DP的图, 如果右边界>左边界 则成水量有左边界决定(维护left_max即可)
// https://leetcode.com/problems/trapping-rain-water/Figures/42/trapping_rain_water.png
namespace so2 {
int trap(vector<int>& A) {
    int left=0; int right=A.size()-1;
    int res=0;
    int maxleft=0, maxright=0;

    while(left<=right) {
        if(A[left]<=A[right]) {  // 这个判断说明 right方向 有更高的柱子, 左边的柱子来决定水量
            if(A[left]>=maxleft) maxleft=A[left];
            else res+=maxleft-A[left];
            left++;
        }
        else{
            if(A[right]>=maxright) maxright= A[right];
            else res+=maxright-A[right];
            right--;
        }
    }
    return res;
}
}

namespace so3 {
// dp和bf 都是求针对当前元素 左右边界的最值
int trap(vector<int>& height) {
    int size = height.size();
    if(size == 0) return 0;
    // 左边第一个大于当前的高度   右边第一个大于当前的高度
    vector<int> left_max(size), right_max(size);

    left_max[0] = height[0];
    // bf:的做法是针对每个元素 一个O(n)遍历
    // dp的改进就是 利用i-1计算过得left_max值 进行比较(用数组存起来)
    //        左边界  i-1  i
    //height   3       2   1       满足单调性
    //  如果left_max[i-1] = 3, height[i] = 1,显然 left_max[i] =left_max[i-1]
    for (int i = 1; i < size; i++) {
        left_max[i] = max(height[i], left_max[i - 1]);
    }
    right_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        right_max[i] = max(height[i], right_max[i + 1]);
    }

    // for (auto i: left_max) cout << i << " ";
    // cout << endl;
    // for (auto i: right_max) cout << i << " ";
    // cout << endl;

    int ans = 0;
    for (int i = 1; i < size - 1; i++) {
        ans += min(left_max[i], right_max[i]) - height[i];
    }
    return ans;
}
}

namespace so4 {
// brute-force; 对于height中(1, n-1)左开右开 的每个元素找到 两侧的柱子(取短板计算)
// https://leetcode.com/problems/trapping-rain-water/solution/
// 缺点: 左右两侧的柱子高度 算得是整个区间的最值
// O(n^2)
int trap(vector<int>& height) {
    int size = height.size();
    if(size == 0) return 0;

    int ans = 0;
    for (int i = 1; i < size - 1; i++) {
        int left_max=0, right_max=0;
        for(int j=i; j>=0; j--) {
            left_max = max(left_max, height[j]);
        }

        for(int k=i; k<size; k++) {
            right_max = max(right_max, height[k]);
        }
        /*  l r i
            1 3 1
            1 3 2
            2 3 3
            2 3 4
            2 3 5
            2 3 6
            3 3 7
            3 2 8
            3 2 9
            3 2 10
         */
        cout << left_max << " " << right_max << " " << i << endl;
        ans += min(left_max, right_max) - height[i];
    }
    return ans;
}
}

int main() {
    vector<int> v = {0,1,0,2,1,0,1,3,2,1,2,1,4};
    // cout << so1::largestRectangleArea(v) << endl;
    cout << so4::trap(v) << endl;

    return 0;
}