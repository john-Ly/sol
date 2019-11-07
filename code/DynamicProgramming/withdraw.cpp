// C++ program for Huffman Coding
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n = 10, k = 5;
int c[10] = {180, 192, 20, 200, 102, 1000, 9, 12, 127, 700};
int r[10] = {70, 192, 1, 10, 6, 60, 4, 1, 8, 100};

// 决策问题 : 将累计排名变为 average 
bool decision(double average) {
	/*
	sum(r[i]) / sum(c[i]) <= x
	sum(r[i]) <= x*sum(c[i])
	0 <= x*sum(c[i]) - sum(r[i])
	0 <= sum(x*c[i] - r[i])
	计算 v[i] = x*c[i] - r[i] 
	*/
	
	vector<double> v;
	for(int i=0; i<n; ++i)
		v.push_back(average * c[i] - r[i]);
	sort(v.begin(), v.end());
	// 此题将变换为 "v中k个元素之和能否大于 0 " 的问题  利用贪心 
	
	double sum = 0;
	for(int i=n-k; i<n; ++i)
		sum += v[i];
	return sum >= 0;
}

// 计算能够得到的最小累计排名 
double optimize() {
	// 累计排名是 [0, 1]之间的实数
	// 循环不变式 !decision(lo) && decision(hi) 
	double lo = -1e-9, hi = 1;
	for(int it=0; it<100; ++it) {
		double mid = (lo + hi) / 2;
		// 能否达到累计排名 mid ? 
		if(decision(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

int main() {
    cout << optimize() << endl;
 
    return 0;
}
