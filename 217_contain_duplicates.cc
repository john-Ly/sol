#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4537029.html
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

// 下标差 最多为k, 存在重复, 返回true
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

namespace sol2 {
// https://www.cnblogs.com/grandyang/p/4545261.html
// 两个数字的坐标差不大于k，值差不大于t
// 差的绝对值不大于t，那么|x - nums[i]| <= t，拆开就是 nums[i] - t <= x <= nums[i] + t,
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    map<long long, int> m;
    int j = 0;   // j-i 维护一个k窗口
    for (int i = 0; i < nums.size(); ++i) {
        if (i-j > k) m.erase(nums[j++]);
        // 绝对值差值表示
        auto a = m.lower_bound((long long)nums[i] - t);
        if (a != m.end() && abs(a->first - nums[i]) <= t) return true;
        m[nums[i]] = i;
    }
    return false;
}
}

int main() {
    vector<int> v = {1,2,3,1};
    cout << containsDuplicate(v) << endl;
    return 0;
}