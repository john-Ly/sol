#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int concat(const vector<int>& lengths) {
	// 声明最小队列
	priority_queue<int, vector<int>, greater<int> > pq;
	for(int i=0; i< lengths.size(); ++i)
		pq.push(lengths[i]);

	int ret = 0;

	// 循环执行 直至剩余 1 个元素
	while(pq.size()-1) {
		int min1 = pq.top(); pq.pop();
		int min2 = pq.top(); pq.pop();

		pq.push(min1+min2);
		ret += min1 + min2;
	}
	return ret;
}

int main() {
	vector<int> len{3,1,3,4,1};
    cout << concat(len) << endl;
    return 0;
}
