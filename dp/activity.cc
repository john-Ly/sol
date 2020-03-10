#include <iostream>
#include <vector>
#include <algorithm>  // sort, max
#include <utility>    // pair
#include <cstring>    // memset()
#include <functional>
#include <map>
#include <queue>      // priority_queue
using namespace std;

/*
1. #include <bits/stdc++.h> 该头文件包含了所有头文件 不过是gcc内部支持，需要预编译 -- 慢
2. http://en.cppreference.com/w/cpp/algorithm/sort   *NICE DEMO*
3. https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/
   - 比较基础的原型题目
4. 堆的特点 插入和删除的时间复杂度
5. meeting2 + schedule 经典题型
*/

int start[] =  {1, 3, 0, 5, 8, 5};
int finish[] = {2, 4, 6, 7, 9, 9};
int n = 6;
// a maximum set of activities that can be done by a single person, one at a time.
//   n -->  Total number of activities
// s[] -->  An array that contains start time of all activities
// f[] -->  An array that contains finish time of all activities

// topic: 题型1 一间办公室最多能有多少个会议可以举行
// O(nlgn) 排序+ O(n)
int schedule() {
	// 按照先结束的顺序排列
	vector<pair<int, int> > order;
	for(int i=0; i<n; ++i)
		order.push_back(make_pair(finish[i], start[i]));
	sort(order.begin(), order.end());

	// earliest: 下一个会议可开始的最早的时间(集合中最后一个会议的结束时间)
	// selected: 目前已选择的会议个数
	cout << "already sorted list: ";
	int lastFinished = 0, selected = 0;
	for(int i=0; i<order.size(); ++i) {
		int meetingstart = order[i].second, meetingfinish = order[i].first;
		if(lastFinished <= meetingstart) {
			lastFinished = meetingfinish;
			++selected;
			cout << i << " ";
		}
	}
	cout << endl;
	return selected;
}

namespace pq {
void SelectActivities(vector<int>s,vector<int>f){
	vector<pair<int,int>> ans;

    // 按照会议结束时间的 最小堆 @TODO 默认pq是最大堆
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> p;
	for(int i=0;i<s.size();i++){
		p.push(make_pair(f[i],s[i]));
	}

	auto it = p.top();
	int start = it.second;
	int end = it.first;
	p.pop();
	ans.push_back(make_pair(start,end));

	while(!p.empty()){
		auto itr = p.top();
		p.pop();
		if(itr.second >= end){
			start = itr.second;
			end = itr.first;
			ans.push_back(make_pair(start,end));
		}
	}

	for(auto& itr: ans)
		cout << "Activity: " << itr.first << "-" << itr.second << endl;
}

// Driver program
void driver () {
	vector<int>s = {1, 3, 0, 5, 8, 5};
	vector<int>f = {2, 4, 6, 7, 9, 9};
	SelectActivities(s,f);
}

}

namespace wjs {
// https://www.geeksforgeeks.org/weighted-job-scheduling/
// 带权重的job 选择
// 动态规划的问题 可以结合LIS的变形
struct Job {
    int start, end;
    int weight;
    Job(int s, int e, int w) : start(s), end(e), weight(w) {}
};

vector<Job> js {{3, 10, 20},
                {1, 2, 50},
                {6, 19, 100},
                {2, 100, 200}};

// using multiset--- lower_bound(这是二分查找)
int cache[7];
int dp(int n) {
	int& ret = cache[n];
	if (n == 1) return ret = js[n-1].weight;
	if(ret != -1) return ret;

	ret = 0;
	int t = js[n-1].start;
	// @TODO 这部分利用 lamda表达式 不能准确表达
	auto it = std::lower_bound(js.begin(), js.end(), t, [](Job& i){
        return i.end < t;
    });

	int pos = std::distance(js.begin(), it);
	selected = max(dp(a, idx-1), 1+dp(a, pos));
	return selected;
}

int s_dp(int idx) {
    // 按照结束时间 升序排列
	sort(js.begin(), js.end(), [](Job& l, Job& r) {
                                         return l.end < r.end;
                                     });
	return dp(idx);
}

}

/*

namespace meetting1 {
// 题目: 一个人能参加完所有的会议吗?
// 思路: 判断一个会议的起始时间是否在 另一个会议的[start, end]之间
// O(n^2)
    struct Interval {
        int start, end;
    }
bool canAttendMeetings(vector<Interval>& intervals) {
    for (int i = 0; i < intervals.size(); ++i) {
        for (int j = i + 1; j < intervals.size(); ++j) {
            if ((intervals[i].start >= intervals[j].start && intervals[i].start < intervals[j].end)
                || (intervals[j].start >= intervals[i].start && intervals[j].start < intervals[i].end)) return false;
        }
    }
    return true;
}

// 排序之后比较即可
bool canAttendMeetings2(vector<Interval>& intervals) {
    // 按照会议起始时间升序
    sort(intervals.begin(), intervals.end(),
                 [](const Interval &a, const Interval &b){return a.start < b.start;});
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i].start < intervals[i - 1].end) {
            return false;
        }
    }
    return true;
}

}

namespace meetting2 {
// 一些会议时间, 请问最少需要几间会议室可以满足(利用贪心算法 求出一间屋子最多可以容纳几场会议)
// map 按照结束时间 升序排列  map[it.end] = it.start
// 可能需要多次遍历 while循环判断 map是否包含东西 @TODO map删除的时间复杂度 + 优先级队列

// topic: 题型2 需要多少办公室最 开完所有会议 (两种题型一致)
// https://www.cnblogs.com/grandyang/p/5244720.html#3964421
int minMeetingRooms(vector<Interval>& intervals) {
    // 按照会议开始时间进行排序
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

*/

int main() {
	cout << "Following activities are selected \n";
    cout << schedule() << endl;
    // pq::driver();
    // {
    //     using namespace wjs;
    //     memset(cache, -1, sizeof(cache));
    //     s_dp(js.size());
    // }

    return 0;
}
