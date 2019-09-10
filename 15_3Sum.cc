#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4481576.html

template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{\n";
	for (vector<T> row: mat) {
        cout << "  [";
		for (T val: row) {
			cout << val << ',';
		}
        cout << "],\n";
	}
    cout << "}\n";
}

// 思路类似 穷举算法
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {};
    // 三个数全为0 或者 TwoSum>0, 后一个数<0
    // leetcode: num.size()-2 报错 @TODO但是感觉不会存在heap memory泄露
    for (int k = 0; k < nums.size()-2; ++k) {
        // 剪枝优化(固定第一位 负数)
        if (nums[k] > 0) break;
        // 重复 与之前的数字 -- 从第二次遍历开始
        if (k > 0 && nums[k] == nums[k - 1]) continue;

        int target = 0 - nums[k];
        // 快慢指针 -- 数组有序可以线性时间O(n), 否则O(n^2)
        // i指针指向小数   j指针指向大数
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target) {
                res.push_back({nums[k], nums[i], nums[j]});
                while (i < j && nums[i] == nums[i + 1]) ++i;
                while (i < j && nums[j] == nums[j - 1]) --j;
                ++i; --j;
            } else if (nums[i] + nums[j] < target) ++i;
            else --j;
        }
    }
    return res;
}

int main() {
    vector<int> v {-4, -1, -1, 0, 1, 2};
    auto tmp = threeSum(v);

    printVector(tmp);
    return 0;
}