#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4341243.html

/*
题目中还要让只遍历一次数组来求解，那么我需要用双指针来做，分别从原数组的首尾往中心移动。

- 定义red指针指向开头位置，blue指针指向末尾位置。
- 从头开始遍历原数组，如果遇到0，则交换该值和red指针指向的值，并将red指针后移一位。若遇到2，则交换该值和blue指针指向的值，并将blue指针前移一位。
   若遇到1，则继续遍历。
*/

void sortColors(vector<int>& nums) {
    vector<int> colors(3);
    for (int num : nums) ++colors[num];

    // 依次遍历color数组
    for (int i = 0, cur = 0; i < 3; ++i) {
        for (int j = 0; j < colors[i]; ++j) {
            nums[cur++] = i;
        }
    }
}

void sortColors3(vector<int>& nums) {
    int red = 0, blue = (int)nums.size() - 1;
    for (int i = 0; i <= blue; ++i) {
        if (nums[i] == 0) {
            swap(nums[i], nums[red++]);
        } else if (nums[i] == 2) {
            swap(nums[i--], nums[blue--]);
        }
    }
}

void sortColors2(vector<int>& nums) {
    int left = 0, right = nums.size() - 1, cur = 0;
    while (cur <= right) {
        if (nums[cur] == 0) {
            // cur之前遇到的数 只有0和1 所以++cur
            swap(nums[cur++], nums[left++]);
        } else if (nums[cur] == 2) {
            // cur这是新替换的值 所以不需要cur++
            swap(nums[cur], nums[right--]);
        } else {
            ++cur;
        }
    }
}

int main() {
    vector<int> v {2,0,2,1,1,0};
    sortColors2(v);

    for(const auto& i : v)
    cout << i << " ";
    cout << endl;

    return 0;
}