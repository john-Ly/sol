#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iterator>
using namespace std;

// https://zhuanlan.zhihu.com/p/70654378
// 中位数用于将集合划分为两个相等长度的子集，一个子集总是大于另一个子集。

class MedianFinder {
public:
    // Adds a number into the data structure.
    void addNum(int num) {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        return small.size() > large.size() ? small.top() : 0.5 *(small.top() - large.top());
    }

private:
    // 默认最大堆
    priority_queue<long> small, large;
};