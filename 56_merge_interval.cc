#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// meeting room 区间范围的比较
// @SEE dp/activity.cc  贪心选择会议室
namespace meeting {
// topic: 题型1 一间办公室最多能有多少个会议可以举行
// O(nlgn) 排序+ O(n)
int minMeetingRooms(vector<Interval>& intervals) {
    // 按照会议结束时间进行排序
    sort(intervals.begin(), intervals.end(),
         [](const auto& a, const auto& b)
             {return a.end < b.end;});

	// lastFinished:
    // 下一个会议可开始的最早的时间(集合中最后一个会议的结束时间)
    // 初始会议结束时间为0/INT_MIN
	int lastFinished = 0, selected = 0;
	for(int i=0; i<intervals.size(); ++i) {
		int start = intervals[i].first, end = intervals[i].second;
		if(lastFinished <= start) {
			lastFinished = end;
			++selected;
		}
	}
	return selected;
}

// topic: 题型2 需要多少办公室最 开完所有会议 (两种题型一致)
// https://www.cnblogs.com/grandyang/p/5244720.html#3964421
int minMeetingRooms(vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b)
                                               {return a.end < b.end;});

    // 最小堆 按照会议结束时间 room
    priority_queue<int, vector<int>, greater<int>> q;

    for (auto a : intervals) {
        // 当前会议可以和queue中的一个会议 共用一个房间(因为该会议的开始 > 结束)
        // 每次都用结束会议最小的来比较  贪心 (如果可以开会, 剔除这个 更新新的会议的结束时间)
        if (!q.empty() && q.top() <= a.start) q.pop();
        q.push(a.end);
    }

    return q.size();
}
}

// @TODO range module 设计
// https://leetcode.com/problems/range-module/
// https://www.cnblogs.com/grandyang/p/8586531.html

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

// leetcode 57: 有序非重叠的区间中插入一个新的区间(可能需要和原有的区间合并)
namespace so1 {
// 非常天才的使用
// https://leetcode.com/problems/insert-interval/discuss/21599/Elegant-C%2B%2B-STL-solution-using-%22equal_range%22-to-find-overlapped-intervals.
// newInterval:          [                      ]
//   intervals: [  ] [  ] [* ]  [ * ]  [ * ]  [*]  []
//                         |                       |
//                        iter1                    iter2
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    // lower_bound计算 comp(it, value)
    // upper_bound计算 !comp(value, it)
    auto compare = [] (const vector<int>& intv1, const vector<int>& intv2)
                       { return intv1.back() < intv2.front(); };
    auto range = equal_range(intervals.begin(), intervals.end(), newInterval, compare);
    auto itr1 = range.first, itr2 = range.second;
    // cout << distance(intervals.begin(), itr1) << endl;
    // cout << distance(intervals.begin(), itr2) << endl;

    if (itr1 == itr2) {
        intervals.insert(itr1, newInterval);
    } else {
        itr2--;
        itr2->front() = min(newInterval.front(), itr1->front());
        itr2->back() = max(newInterval.back(), itr2->back());
        // 左闭右开
        intervals.erase(itr1, itr2);
    }
    return intervals;
}
}

namespace so2 {
// https://leetcode.com/problems/insert-interval/discuss/21669/Easy-and-clean-O(n)-C%2B%2B-solution
// 主要就是把原数组分成三部分  两边不重叠+中间重叠
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    // 使用了一个额外的数组
    vector<vector<int>> res;
    int index = 0;
    while(index < intervals.size() && intervals[index].back() < newInterval.front()){
        res.push_back(intervals[index++]);
    } // index离开循环后 指向了lower_bound

    while(index < intervals.size() && intervals[index].front() <= newInterval.back()){
        newInterval.front() = min(newInterval.front(), intervals[index].front());
        newInterval.back() = max(newInterval.back(), intervals[index].back());
        index++;
    } // index离开循环 指向upper_bound

    res.push_back(newInterval);
    while(index < intervals.size()){
        res.push_back(intervals[index++]);
    }
    return res;
}
}

namespace so3 {
// https://leetcode.com/problems/merge-intervals/discuss/21242/C%2B%2B-10-line-solution.-easing-understanding
// 区间合并  ([1,4] + [4,5] => [1,5])
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end(), [] (const vector<int>& intv1, const vector<int>& intv2)
                                                { return intv1.front() < intv2.front(); });
    res.push_back(intervals.front());
    for (int i = 1; i < intervals.size(); ++i) {
        if (res.back().back() < intervals[i].front())
            // res最后一个元素 与 当前 没有overlap, 直接添加
            res.push_back(intervals[i]);
        else
            // 否则 更新最后一个的 结束时间
            res.back().back() = max(res.back().back(), intervals[i].back());
    }
    return res;
}
}

namespace so4 {
// 总结区间  ([1,2, 4,5] ==> [4,5] [1,2])
// 思路: 遍历区间
// 228  https://www.cnblogs.com/grandyang/p/4603555.html
vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    int i = 0, n = nums.size();
    while (i < n) {
        int j = 1;
        while (i+j < n && nums[i+j] == nums[i]+j) ++j;

        // 退出循环 j代表连续数字的个数
        res.push_back(j>1 ? to_string(nums[i]) + "->" + to_string(nums[i + j - 1]) : to_string(nums[i]));
        i += j;
    }
    return res;
}
}

namespace so5 {
// @TODO
// 缺失区间  ([1,2, 4,5] ==> [4,5] [1,2])
// [0, 1, 3, 50, 75] 上下界[0,99] ==> [2, 4->49, 51->74, 76->99]
// 163 https://www.cnblogs.com/grandyang/p/5184890.html
vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> res;
    int l = lower;
    for (int i = 0; i <= nums.size(); ++i) {
        int r = (i < nums.size() && nums[i] <= upper) ? nums[i] : upper + 1;
        if (l == r) ++l;
        else if (r > l) {
            res.push_back(r - l == 1 ? to_string(l) : to_string(l) + "->" + to_string(r - 1));
            l = r + 1;
        }
    }
    return res;
}
}

int main() {
    // vector<vector<int>> v {{1, 2}, {3,5}, {6,7}, {8, 10}};
    // vector<int> ni {4, 8};
    // printVector( so1::insert(v, ni) );
    // printVector( so2::insert(v, ni) );

    {
        using namespace so3;
        vector<vector<int>> v {{1, 3}, {2,6}, {15,18}, {8, 10}};
        printVector(merge(v));
    }

    return 0;
}