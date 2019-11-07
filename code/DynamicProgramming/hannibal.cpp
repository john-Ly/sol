#include <iostream>
#include <vector>
#include <cstring> // memset()
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n, day, p, q;
int connected[5][5] = {{0,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,0}, {1,0,0,0,0}, {0,1,0,0,0}};
int deg[5] = {3, 2, 1, 1, 1};

// 穷举搜索法的思路还是很清晰的 
// path:
// 1. path 的首元素是 监狱的位置 ; 最后一个元素是当前位置: 决定下一个村子时会用到 
// 2. path 的长度与逃狱后经过的天数 相关
// 3. 计算概率: 计算已完成路径的概率时 用到 
double search(vector<int>& path) {
	if(path.size() == day+1) {
		if(path.back() != q) return 0.0;
		double ret = 1.0;
		for(int i=0; i+1<path.size(); ++i)
		    ret /= deg[path[i]];
		
		return ret;
	}
	
	double ret = 0;
	for(int there=0; there<n; ++there) {
		if(connected[path.back()][there]) {
			path.push_back(there);
			ret += search(path);
			path.pop_back();
		}
	}
	return ret;
}

double cache[51][101];
double search2(int here, int days) {
	// 第 0 日的情况 
	if(days == 0) return (here == q ? 1.0 : 0.0);
	
	double& ret = cache[here][days];
	if(ret > -0.5) return ret;
	
	ret = 0.0;
	for(int there=0; there<n; ++there) {
		if(connected[here][there]) {
			ret += search2(there, days-1) / deg[here];
		}
	}
    return ret;
}

int main() {
	memset(cache, -1, sizeof(cache));
    vector<int> tmp;
    p = 0; tmp.push_back(p);
    day = 2; q = 4; n = 5;
	 
	double probability = search(tmp);
    cout << probability << endl;
    cout << search2(p, day) << endl;

    return 0;
}
