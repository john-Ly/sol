#include <vector>
#include <iostream>
using namespace std;

// https://leetcode.com/problems/move-zeroes/solution/

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
// partition283
void moveZeroes(vector<int>& nums) {
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        if (nums[i]) {
            swap(nums[i], nums[j++]);
        }
    }
}

// 奇数排在前面 偶数排在后面 但是顺序变换了
void moveEvens(vector<int>& nums) {
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        // cout << i << '-' << j << ": ";
        if (nums[i]%2 != 0) {
            swap(nums[i], nums[j++]);
        }
        // pv(nums);
    }
}

// 快慢指针 占用太多内存
void reOrderArray(vector<int> &array) {
    deque<int> result;
    int num = array.size();
    for(int i = 0; i < num; i++){
        if(array[num - i - 1] % 2 == 1){
            result.push_front(array[num - i - 1]);
        }
        if(array[i] % 2 == 0){
            result.push_back(array[i]);
        }
    }
    array.assign(result.begin(),result.end());
}

int main() {
    vector<int> v = {0,1,0,3,12};
    moveZeroes(v);
    moveEvens(v);
    return 0;
}