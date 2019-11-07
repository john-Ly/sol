// C++ program for Huffman Coding
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

#define size 6

// 预先计算出两个基地间距
double dist[size][size] = {0}; // 快速初始化二维数组 
// 只连接了相隔距离小于 d 的基地时, 返回所有基地是否都连接到一起 
bool decision(double d) {
	vector<bool> visited(size, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	
	int seen = 0;
	while(!q.empty()) {
		int here = q.front(); q.pop();
		++seen;
		for(int there=0; there<size; ++there) {
			if(!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
		}
	}
	return seen == size;
}

// 返回能够连接所有基地的最小的 d 
double optimize() {
	double lo = 0, hi = 1416.00; 
	for(int it=0; it<100; ++it) {
		double mid = (lo + hi) / 2;
		// 如果 mid 可以连接所有基地, 则寻找更好(小)的结果 
		if(decision(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

int main() {
	vector<pair<double, double> > coordinate {{1.0, 1.0}, {30.91, 8}, 
						{4.0, 7.64}, {21.12, 6.0}, {11.39, 3.0}, {5.31, 11.0}};
	
	for(int i=0; i<=size; ++i) {
		for(int j=0; j<=size; ++j) {
			if(dist[j][i] == 0) { 
				double dx = coordinate[i].first-coordinate[j].first;
			    double dy = coordinate[i].second-coordinate[j].second;
				dist[i][j] = sqrt(dx*dx + dy*dy);
			} else 
			  	dist[i][j] = dist[j][i];
		}
	}
/*  这组数据是没有利用 矩阵对称的性质 全部计算 但是有错误出现 
0       30.7182 7.28626 20.732  10.5807 10.8893 30.7182
30.7182 0       26.9124 9.9922  20.1502 25.7752 7.28626
7.28626 26.9124 0       17.1984 8.72592 3.60634 20.732
20.732  9.9922  17.1984 0       10.182  16.5818 10.5807
10.5807 20.1502 8.72592 10.182  0       10.0482 10.8893
10.8893 25.7752 3.60634 16.5818 10.0482 0       1.41421
1.41421 31.9285 8.62378 21.9557 11.7785 12.2146 0

	for(int i=0; i<=size; ++i) {
		cout << endl << endl << endl;
		for(int j=0; j<=size; ++j)
			cout << dist[i][j] << "\t"; 
	}

  利用镜像对称性质 --- 后面补充 @TODO 
0       30.7182 7.28626 20.732  10.5807 10.8893 30.7182


30.7182 0       26.9124 9.9922  20.1502 25.7752 7.28626


7.28626 26.9124 0       17.1984 8.72592 3.60634 20.732


20.732  9.9922  17.1984 0       10.182  16.5818 10.5807


10.5807 20.1502 8.72592 10.182  0       10.0482 10.8893


10.8893 25.7752 3.60634 16.5818 10.0482 0       30.7182


30.7182 7.28626 20.732  10.5807 10.8893 30.7182 0
*/ 
    cout << optimize() << endl;
 
    return 0;
}
