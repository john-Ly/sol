// 平均数-mean
// 中位数-median
// 众数-mode (有限区间)

// 如果是无限区间(抽奖算法)
// 随机算法

#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// https://leetcode.com/problems/majority-element/discuss/51612/C%2B%2B-6-Solutions
// 题目要求 数量超过半数的元素(取下整) == majarity

int findMedian(vector<int>& v) {
    auto half = v.size() / 2;
    std::nth_element(v.begin(), v.begin() + half, v.end());
    if (v.size() % 2 == 0) { return (v[half] + v[half-1]) / 2; }
    else { return v[half]; }
}

int majorityElement1(vector<int>& nums) {
    //           ele: cnt
    // 需要初始化为0吗
    unordered_map<int, int> counter;
    for (int num : nums) {
        if (++counter[num] > nums.size() / 2) {
            return num;
        }
    }
    return 0;
}

// Since the majority element appears more than n / 2 times, the n / 2-th element in the sorted nums must be the majority element.
int majorityElement2(vector<int>& nums) {
    nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
    return nums[nums.size() / 2];
}

// 理解下分治的重要性
namespace divide_conquer {
int majority(vector<int>& nums, int l, int r) {
    // only one ele in vector
    if (l == r) { return nums[l]; }

    int m = l + (r - l) / 2, lm = majority(nums, l, m), rm = majority(nums, m + 1, r);
    // same majority result from two halves
    if (lm == rm) { return lm; }

    // 用了标准库算法 感觉得不偿失
    int lcnt = count(nums.begin() + l, nums.begin() + r + 1, lm);
    int rcnt = count(nums.begin() + l, nums.begin() + r + 1, rm);
    return lcnt > rcnt ? lcnt : rcnt;
}

int majorityElement(vector<int>& nums) {
    return majority(nums, 0, nums.size() - 1);
}

}

namespace moore_voting {
// like MEA
/*
if (map.count(pageaddr) != 0) {
    map[pageaddr]++;
}  // 1. already in map
else if (map.size() < num) {
    map[pageaddr] = 1;
}       // 2. not find in map && map has extra room
else {  // 3. for each one, subtract one(remove item when it's value reached zero)
    for (auto& item : map) item.second--;
    for (auto it = begin(map); it != end(map);) {
    if (it->second == 0) {
        it = map.erase(it);
    } else
        ++it;
    }
}
*/

// 算法前提 数组中一定存在超过半数的元素
// https://www.cnblogs.com/grandyang/p/4233501.html
// https://leetcode.com/problems/majority-element/solution/
// http://www.cs.utexas.edu/~moore/best-ideas/mjrty/
int majorityElement(vector<int>& nums) {
    int counter = 0, majority;
    for (int num : nums) {
        if (!counter) {
            majority = num;
        }
        counter += (num == majority ? 1 : -1);
    }
    return majority;
}

}

// The bits in the majority are just the majority bits of all numbers.
int majorityElement3(vector<int>& nums) {
    int majority = 0;

    // mask <<= 1 不能选用i 会超出范围
    for (unsigned int i = 0, mask = 1; i < 32; i++, mask <<= 1) {
        // cout << "i/mask: " << i << ' ' << mask << '\n';
        int bits = 0;
        for (int num : nums) {
            // & 的运算结果为 0 或者 mask
            if (num & mask) {
                bits++;
            }
        }
        // 添加该位
        if (bits > nums.size() / 2) {
            majority |= mask;
        }
    }
    return majority;
}


// @TODO bit位操作的总结
// 191_number_of_bits
int hammingWeight(uint32_t n) {
    int res = 0;

    // mask <<= 1 不能选用i 会超出范围
    for (unsigned int i = 0, mask = 1; i < 32; i++, mask <<= 1) {
        // & 的运算结果为 0 或者 mask
        if (n & mask) { ++res; }
    }
    return res;
}

// 231_power_of_two
// https://www.cnblogs.com/grandyang/p/4623394.html
// 如果是2的幂次 二进制表示只有1个1
bool isPowerOfTwo(int n) {
    // 这种方法很巧妙 n-1  造成高位为0 低位为1   与原来的值相与得到结果
    return (n > 0) && (!(n & (n - 1)));
}


// 326_power_of_three
namespace p_3 {
// https://www.cnblogs.com/grandyang/p/5138212.html
bool isPowerOfThree(int n) {
    // n为负数或者0 是corner-case
    while (n && n % 3 == 0) {
        n /= 3;
    }
    return n == 1;
}

// 换底公式 (log10)
// a - int(a) == 0   判断一个数为 整数
bool isPowerOfThree(int n) {
    return (n > 0 && int(log10(n) / log10(3)) - log10(n) / log10(3) == 0);
}

// https://www.cnblogs.com/grandyang/p/5403783.html
// 4的幂次  前两种方法是通用的
// 324_power_four


//   可以判断出是 2的幂次          1010101010101010101010101010101  因为4的幂次
// return num > 0 && !(num & (num - 1)) && (num & 0x55555555) == num;
    // (num - 1) % 3 == 0; // 4的幂次-1 都能被3整除
}

// 190_reverseBits
// 先处理最低位(类似处理数组的最后一位)
// https://www.cnblogs.com/grandyang/p/4321355.html
uint32_t reverseBits(uint32_t n) {
    uint32_t res;
    for (unsigned int i = 0; i < 32; ++i) {
        if (n & 1u) {
            // 或运算 相当于加法
            res = (res << 1u) | 1u;
        } else {
            res <<= 1u;
        }
        n >>= 1u;
    }
    return res;
}

// 挑选出 超过 n/3 取下整的 众数
// 最多只有两个满足 (如果三个满足 n个数就超了 所以最多两个)
// https://leetcode.com/problems/majority-element-ii/discuss/63520/Boyer-Moore-Majority-Vote-algorithm-and-my-elaboration
// https://www.cnblogs.com/grandyang/p/4606822.html
vector<int> majorityElement4(vector<int>& nums) {
    vector<int> res;
    int a = 0, b = 0, cnt1 = 0, cnt2 = 0, n = nums.size();
    // 1. 找出候选者 但是cnt可能打乱了
    for (int num : nums) {
        // 基本思路还是 moore的方法
        if (num == a) ++cnt1;
        else if (num == b) ++cnt2;
        else if (cnt1 == 0) { a = num; cnt1 = 1; }
        else if (cnt2 == 0) { b = num; cnt2 = 1; }
        else { --cnt1; --cnt2; }
    }
    // 2. 确定两个候选者的cnt
    cnt1 = cnt2 = 0;
    for (int num : nums) {
        if (num == a) ++cnt1;
        else if (num == b) ++cnt2;
    }
    if (cnt1 > n / 3) res.push_back(a);
    if (cnt2 > n / 3) res.push_back(b);
    return res;
}


int main() {
    std::vector<int> v {5, 6, 4, 3, 2, 6, 7, 9, 3, 10};
    std::vector<int> v2 {5, 6, 4, 3, 2, 6, 7, 9, 3};

    std::vector<int> v3 {7, 7, 5, 7, 5, 1 , 5, 7 , 5, 5, 7, 7 , 7, 7, 7, 7};
    cout << findMedian(v) << '\n';

    cout << majorityElement3(v3) << '\n';

    int a = 2;
    cout << (a & 3) << '\n';
    return 0;
}