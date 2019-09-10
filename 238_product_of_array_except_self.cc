#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 不能使用除法
// https://www.cnblogs.com/grandyang/p/4650187.html
namespace so1 {
// https://leetcode.com/problems/product-of-array-except-self/Figures/238/diag-1.png
// 主要理解图示()
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> fwd(n, 1), bwd(n, 1), res(n);
    for (int i = 0; i < n - 1; ++i) {
        fwd[i + 1] = fwd[i] * nums[i];
    }
    for (int i = n - 1; i > 0; --i) {
        bwd[i - 1] = bwd[i] * nums[i];
    }

    for (int i = 0; i < n; ++i) {
        res[i] = fwd[i] * bwd[i];
    }
    return res;
}
}

namespace so2 {
// space: O(1)
vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> res(nums.size(), 1);
    for (int i = 1; i < nums.size(); ++i) {
        res[i] = res[i - 1] * nums[i - 1];
    }
    int right = 1;
    for (int i = nums.size() - 1; i >= 0; --i) {
        res[i] *= right;
        right *= nums[i];
    }
    return res;
}
}

int main() {
    vector<int> v = {2,1,5,6,2,3};
    // cout << so1::productExceptSelf(v) << endl;

    return 0;
}