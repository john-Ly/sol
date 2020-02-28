#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iterator>
using namespace std;

// https://www.cnblogs.com/grandyang/p/6620334.html
// Sliding Window Median

// https://zhuanlan.zhihu.com/p/70654378
// 中位数用于将集合划分为两个相等长度的子集，一个子集总是大于另一个子集。

// https://www.cnblogs.com/grandyang/p/4896673.html
// https://leetcode.com/problems/find-median-from-data-stream/solution/
class MedianFinder {
public:
    // Adds a number into the data structure.
    void addNum(int num) {
        // 像是流水线
        // small先接受新数据  large得到max(small)中
        small.push(num);

        large.push(-small.top());
        small.pop();

        // 调整大小
        if (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        // 奇数个数, 返回smaller的最大的数
        if (small.size() > large.size()) return small.top();
        // 可能会溢出
        else return 0.5 *(small.top() - large.top());
    }

private:
    // 默认最大堆
    priority_queue<long> small, large;
    // priority_queue<int, vector<int>, greater<int>> large; // min heap
};

// https://zhuanlan.zhihu.com/p/70654378
// https://www.cnblogs.com/grandyang/p/4465932.html

// https://www.cnblogs.com/tenosdoit/p/3554479.html
// https://liam.page/2019/08/22/find-median-of-two-sorted-arrays/

// 4 median of two sorted Arrays
// 思路是中位数是两个数量相等的集合 max(左集合) <= min(右集合)  大小关系
// 简单思路: 1. 采用归并排序  相当于多个有序数组 进行归并排序
//           2. 得到一个有序数组 求中位数     O(log(m+n))
//