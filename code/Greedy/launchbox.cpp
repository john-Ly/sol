#include <iostream>
#include <vector>
#include <set>        // multiset
#include <algorithm>  // sort, max
#include <utility>    // pair
using namespace std;

vector<int> heating{1, 2, 3};
vector<int> eat{1, 2, 1};
int n = 3;

int heat() {
	// 决定先加热的顺序
    //    享用时间   序号
	vector<pair<int, int> > order;

	for(int i=0; i<n; ++i)
		order.push_back(make_pair(-eat[i], i));
    // sort对一个 vector<int> 进行降序排列; 但是题目中存放的是pair 采用 -eat[i] 简化降序
    // std::sort(s.begin(), s.end(), std::greater<int>());
	sort(order.begin(), order.end());  // 按照 便当 享用时间最长的来排序

	// for(auto i: order)
    // 	cout << "\n(" << i.first << ", " << i.second << ")\n";

	// 模拟出按照当前顺序加热并享用的过程
    // 吃完某个便当所需时间 = 目前位置加热所有便当耗费的时间 + 享用当前便当所需时间
	int ret = 0, beginEat = 0;
	for(int i=0; i<order.size(); ++i) {
		int box = order[i].second;  // 享用时间最长的 便当
		beginEat += heating[box];
		// max可以判断 加热的时间在前一便当加热和吃的时间之内
		ret = max(ret, beginEat + eat[box]);
	}
	return ret;
}

int main() {
    cout << "\nminimum launch time:" <<heat() << endl;
    return 0;
}
