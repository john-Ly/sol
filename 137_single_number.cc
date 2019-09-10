#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4263927.html

// https://cloud.tencent.com/developer/article/1131946
// 这个博客理解的比较好  就是统计然后取模
int singleNumberTriple(vector<int>& nums) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        int sum = 0;
        // 遍历数组 取每个数的第i位(从低位到符号位) count
        for (int j = 0; j < nums.size(); ++j) {
            sum += (nums[j] >> i) & 1;
        }
        // |= 添加某位元素
        res |= (sum % 3) << i;
    }
    return res;
}

// https://cloud.tencent.com/developer/article/1131945
// 这个思路比较巧妙 记住
// @TODO 利用两个数来表示%3
// 好像理解了 leetcode上面的解法
int singleNumber(vector<int>& nums) {
    int a = 0, b = 0;
    for (int i = 0; i < nums.size(); ++i) {
        b = (b ^ nums[i]) & ~a;
        a = (a ^ nums[i]) & ~b;
    }
    return b;
}

int singleNumber_bit(vector<int>& nums) {
    int res = 0;
    for (auto num : nums) res ^= num;
    return res;
}

int main () {
    vector<int> v {2,1,2};
    int tmp = singleNumber(v);

    std::cout << tmp << std::endl;
    return 0;
}
