#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 线性同余随机数生成器 
// A[0] = 1983
// A[i] = (A[i-1]*a+b) mod 20090711
struct RNG {
    int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) { }
	
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int> > maxHeap;
	priority_queue<int, vector<int>, greater<int> > minHeap;
	int ret = 0;
	// 循环不变式
	// 1. maxHeap 的大小与 minHeap 相等或大于 1。
	// 2. maxHeap.top() <= minHeap.top()
	
	for(int cnt=1; cnt<=n; ++cnt) {
		if(maxHeap.size() == minHeap.size())
		    maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		
		if(!minHeap.empty() && !maxHeap.empty() 
		    && minHeap.top() < maxHeap.top() ) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main()
{	
	RNG rng(1, 1);
	int ret = runningMedian(10, rng);
	cout << ret << endl;

    return 0;
}
