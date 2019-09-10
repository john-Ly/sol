#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

const int MIN = numeric_limits<int>::min();

// 仅针对数值类型进行比较
template <class T>
T maxNumInThree(T a, T b, T c) {
    T max;
    max = (a > b) ? a : b;
    max = (max > c) ? max : c;

    return max;
}


// https://unclegem.cn/2018/08/10/Leetcode%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0-152-%E4%B9%98%E7%A7%AF%E6%9C%80%E5%A4%A7%E5%AD%90%E5%BA%8F%E5%88%97/
// https://leetcode.com/problems/maximum-product-subarray/discuss/203013/C%2B%2B-O(N)-time-O(1)-space-solution-with-explanation
// 解释详细: 全是正数 + 正数和0混合 +         正数,0,负数 三种情况
//           累积求和  类似最大连续子数组和

namespace positive {
int allPositive(vector<int>& nums) {
    int runningProduct = 1;
    for (int n: nums) {
        runningProduct *= n;
    }
    return runningProduct;
}
}

namespace pos_zero {
int zeroPositive(vector<int>& nums) {
    int best = MIN;
    int runningProduct = 1;
    for (int n: nums) {
        runningProduct = max(runningProduct * n, n);
        best = max(runningProduct, best);
    }
    return best;
}
}

namespace pos_zero_neg {
// https://www.cnblogs.com/grandyang/p/4028713.html
int maxProduct(vector<int>& nums) {
    if (nums.empty()) return 0;

    int best = MIN;
    // Running products
    int maxProd = 1;
    int minProd = 1;

    for (int n: nums) {
        /*
        1. 当遍历到一个正数时，此时的最大值等于之前的最大值乘以这个正数和当前正数中的较大值，此时的最小值等于之前的最小值乘以这个正数和当前正数中的较小值。
        2. 当遍历到一个负数时，我们先用一个变量t保存之前的最大值mx，然后此时的最大值等于之前最小值乘以这个负数和当前负数中的较大值，此时的最小值等于之前保存的最大值t乘以这个负数和当前负数中的较小值。
         */
        if (n < 0) {
            // Swap max and min
            swap(maxProd, minProd);
        }
        // Reset to current value if smaller or larger than it
        // (intuitively means that we start considering a new sub-array)
        maxProd = max(maxProd*n, n);
        minProd = min(minProd*n, n);
        best = max(best, maxProd);
    }

    return best;
}
}

int main() {
    vector<int> a {-2,0, -1 };

    cout << pos_zero_neg::maxProduct(a) << endl;
    return 0;
}
