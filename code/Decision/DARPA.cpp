// C++ program for Huffman Coding
#include <iostream>
#include <vector>
using namespace std;

// 决策问题: 返回已排好序的 locations 中, 是否存在方法使得如果选择 cameras 个数后
// 所有摄像机的间隔都能达到 gap 以上
bool decision(const vector<double>& locations, int cameras, double gap) {
	// 每次能够架设摄像机时都架设的贪婪算法
	double limit = -1;
	int installed = 0;
	for(int i=0; i<locations.size(); ++i) {
		if(limit <= locations[i]) {
			++installed;
			// 至少在 location[i]+gap 之后的位置才能架设摄像机
			limit = locations[i] + gap; 
		}
	}
	// 最终能够架设 cameras 个以上的摄像机就成功
	return installed >= cameras; 
}

double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	// 循环不变式: decision(lo) && ！decision(hi)
	for(int it=0; it<100; ++it) {
		double mid = (lo + hi) / 2.0;
		// 间隔能够达到 mid 以上, 则答案就在区间[mid, hi]
		if(decision(location, cameras, mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main() {
	vector<double> locations {0, 70, 90, 120, 200, 210, 220, 240};
	int m = 4;
    cout << optimize(locations, m) << endl;
 
    return 0;
}
