#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4537029.html
// @TODO 还有III 没有处理

namespace sol1 {
bool containsDuplicate(vector<int>& nums) {
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++i) {
        if (m.find(nums[i]) != m.end()) return true;
        ++m[nums[i]];
    }
    return false;
}

// sort(nums.begin(), nums.end());
// for (int i = 1; i < nums.size(); ++i) {
//     if (nums[i] == nums[i - 1]) return true;
// }
// return false;
}

namespace sol2 {
// 下标差 最多为k, 存在两个重复, 返回true
// @NOTE 利用滑动窗口+下标递增  方便求出绝对距离

// nums = [1,2,3,1,2,3], k = 2  ==> false
bool containsDuplicate(vector<int>& nums) {
    //           数    下标
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++i) {
        if (m.find(nums[i]) != m.end() && i - m[nums[i]] <= k) return true;
        else m[nums[i]] = i;
    }
    return false;
}

}

namespace sol2 {
}

int main() {
    vector<int> v = {1,2,3,1};
    cout << containsDuplicate(v) << endl;
    return 0;
}