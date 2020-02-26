#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>  // rand

// topic: random 概率

// @TODO 还有follow up
// https://www.cnblogs.com/grandyang/p/5740864.html
class RandomizedSet {
public:
    // 如果已经存在 返回false
    // 否则, 更新hash/vec
    bool insert(int val) {
        if (m.count(val)) return false;
        nums.push_back(val);
        m[val] = nums.size() - 1;
        return true;
    }

    // 如果不存在, 返回false
    bool remove(int val) {
        if (!m.count(val)) return false;
        int point = m[val];
        // 数组实现常数删除
        int last = nums.back();
        nums[point] = last;
        m[last] = point;
        nums.pop_back();
        m.erase(val);
        return true;
    }

    int getRandom() { return nums[rand() % nums.size()]; }

private:
    // 存储数字
    vector<int> nums;
    //          数字 和 下标
    unordered_map<int, int> m;
};