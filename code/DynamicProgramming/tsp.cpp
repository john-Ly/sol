#include <iostream>
#include <vector>
#include <algorithm>  // max, sort
#include <utility>  // pair
#include <cstring> // memset()
using namespace std;
// 与汉尼拔的那一道题目 很相似
// 可以正反 两个方面选择路径 
// 未完成！！！！！！！！ 

const int INF = 987654321;

int n; // 城市个数
double dist[MAX][MAX];  // 两城间距
// path: 已检索的路径 
// visited: 对各城市访问与否 
// currentLength: 所有已检索路径的长度 
// 在访问所有剩余城市的路径中 返回最短路径
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	// 初试部分 所有城市都已访问完毕 则回到起始城市 终止计算 
	if(path.size() == n)
        return currentLength + dist[path[0]][path.back()];
	
	double ret = INF;
	// 尝试所有可能的下一个要访问的城市
	for(int next=0; next<n; ++next) {
		if(visited[next]) continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;
		// 利用递归调用完成剩余路径的检索 并得出最短路径的长度
		double cand = shortestPath(path, visited, currentLength+dist[here][next]);
		ret = min(ret, cand);
		
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}

double cache[MAX][1<<MAX];
double shortestPath(int here, int visited) {
	// 第 0 日的情况 
	if(visited == (1<<n)-1 ) return dist[here][0];
	
	double& ret = cache[here][visited];
	if(ret >= 0) return ret;
	
	ret = INF;
	// 尝试所有要访问的下一个城市 
	for(int there=0; there<n; ++there) {
		if(visited & (1<<n) ) continue;
		double cand = dist[here][next] + shortestPath2(next, visited+(1<<next));
		ret = min(ret, cand);
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
