#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
*/
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

namespace so1 {
// 非常天才的使用
// https://leetcode.com/problems/insert-interval/discuss/21599/Elegant-C%2B%2B-STL-solution-using-%22equal_range%22-to-find-overlapped-intervals.
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
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end(), [] (const vector<int>& intv1, const vector<int>& intv2)
                                                { return intv1.front() < intv2.front(); });
    res.push_back(intervals.front());
    for (int i = 1; i < intervals.size(); i++) {
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