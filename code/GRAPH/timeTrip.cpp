#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <utility>  // std::pair
#include <algorithm>
#include <limits>   // numeric_limits
using namespace std;

auto INF = std::numeric_limits<int>::max();
// 顶点个数 
const int V = 4;
// 图 邻接表 保存成对(连接的顶点序号, 边线加权值)
vector<pair<int, int> > adj[V];
// reachable[u][v] = u 到 v 的路径存在吗 ?
bool reachable[V][V];

// 计算 src 到 target 的最短路径
// 如果存在加权值等于 负无穷大的路径, 则返回 -INF 
vector<int> bellman2(int src, int target) {
	// 除了起点 所有顶点的最短距离的上限为 INF
	vector<int> upper(V, INF);
	upper[src] = 0;
	
	// 遍历 V-1 次
	for(int iter=0; iter<V-1; ++iter) {
		for(int here=0; here<V; ++here)
			for(int i=0; i<adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				// 沿 (here, there) 边线放缩
				upper[there] = min(upper[here], upper[here] + cost);
			}
	}
	// 确认是否存在负权回路
	for(int here=0; here<V; ++here)
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			// 如果松弛操作成功 那么 here 和 there 都在负权回路中 
			if(upper[there] > upper[here] + cost) {
				// 是否有包含此负权回路的路径
				if(reachable[src][here] && reachable[here][target])
					return -INF;
			}
		}
	
	return upper[target];
}

int main() {
	// normal-test
	adj[0].push_back(make_pair(2, -7)); adj[0].push_back(make_pair(3, -4));
	adj[2].push_back(make_pair(1, 3));
	adj[3].push_back(make_pair(2, 9));

	// corner-test
/*	adj[0].push_back(make_pair(1, 4)); adj[0].push_back(make_pair(2, 4));
	adj[2].push_back(make_pair(3, -7));
	adj[3].push_back(make_pair(2, 5));
	adj[4].push_back(make_pair(1, -4)); adj[4].push_back(make_pair(4, -1));*/
	
	return 0;
}
