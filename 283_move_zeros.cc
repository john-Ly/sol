#include <vector>
#include <iostream>
using namespace std;

// https://leetcode.com/problems/move-zeroes/solution/
// 快慢指针

void moveZeroes(vector<int>& nums) {
    int lastNonZero = 0;
    // 把所有非0数字 重头赋值到
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0)
            nums[lastNonZero++] = nums[i];
    }

    // 输入序列为 [0000...1] 会有O(n)的不必要操作
    // 后面所有都填充为0
    for (int i = lastNonZero; i < nums.size(); ++i) {
        nums[i] = 0;
    }
}

void pv(vector<int>& v) {
    for (auto i : v)
        std::cout << i << ' ';
    cout << "\n";
}

// 不变式:
//     1. slow_pointer之前 的元素全部是 non-zero
//     2. slow_pointer和fast_pointer之间 全是zero
// fast快于slow 所以fast遇到non-zero就交换到slow之前了 所以成立
void moveZeroes(vector<int>& nums) {
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        // cout << i << '-' << j << ": ";
        if (nums[i]) {
            swap(nums[i], nums[j++]);
        }
        // pv(nums);
    }
}

int main() {
    vector<int> v = {0,1,0,3,12};
    moveZeroes(v);
    return 0;
}
