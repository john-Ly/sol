#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ����ͬ������������� 
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
	// ѭ������ʽ
	// 1. maxHeap �Ĵ�С�� minHeap ��Ȼ���� 1��
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
