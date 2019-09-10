#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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
int threeSumClosest(vector<int>& nums, int target) {
    int closest = nums[0] + nums[1] + nums[2];
    int diff = std::abs(closest - target);
    sort(nums.begin(), nums.end());
    for (int k = 0; k < nums.size()-2; ++k) {
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            int sum = nums[k] + nums[i] + nums[j];
            int newDiff = std::abs(target-sum);
            if (newDiff < diff) {
                diff = newDiff;
                closest = sum;
            }

            if (sum < target) ++i;
            // sum >= target
            else --j;
        }
    }
    return closest;
}

int main() {
    vector<int> v {-4, -1, 1, 2};
    auto tmp = threeSumClosest(v, 1);
    cout << tmp << endl;

    return 0;
}