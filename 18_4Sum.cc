#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 

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

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n-3; ++i) {
        // 重复 与之前的数字 -- 从第二次遍历开始
        if (i > 0 && nums[i] == nums[i-1]) continue;
        for (int j = i+1; j < n-2; ++j) {
            if (j > i+1 && nums[j] == nums[j-1]) continue;
            int lo = j + 1, hi = n - 1;
            while (lo < hi) {
                int sum = nums[i] + nums[j] + nums[lo] + nums[hi];
                if (sum == target) {
                    res.push_back({nums[i], nums[j], nums[lo], nums[hi]});
                    while (lo < hi && nums[lo] == nums[lo + 1]) ++lo;
                    while (lo < hi && nums[hi] == nums[hi - 1]) --hi;
                    ++lo; --hi;
                } else if (sum < target) ++lo;
                else --hi;
            }
        }
    }
    return res;
}

int main() {
    vector<int> v {1, 0, -1, 0, -2, 2};
    auto tmp = fourSum (v, 0);
    printVector(tmp);
    return 0;
}
