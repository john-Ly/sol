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
const int V = 7;
// 图 邻接表 保存成对(连接的顶点序号, 边线加权值)
vector<pair<int, int> > adj[V];

// O(|V||E|) 
// 如果存在负权回路, 则返回空数组 
vector<int> bellmanFord(int src) {
	// 除了起点 所有顶点的最短距离的上限为 INF
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;
	
	// 遍历 V 次
	for(int iter=0; iter<V; ++iter) {
		updated = false;
		// 两次 for 循环 来对所有边线松弛 
		for(int here=0; here<V; ++here)
			for(int i=0; i<adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
									cout << there << "=========" << here << endl;
					cout << upper[there] << " " << upper[here] << " " << cost << endl;
				// 尝试沿 (here, there) 边线放缩
				if(upper[there] > upper[here] + cost) {
					// 成功
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
			
		// 对所有边线松弛操作都失败后, 没有必要循环 V-1 次 直接终止
		if(!updated) break; 
	}
	// 第 V 次遍历成功执行了松弛操作 必定存在负权回路
	if(updated) upper.clear();
	
	return upper;
}

int main() {
	adj[0].push_back(make_pair(1, 5)); adj[0].push_back(make_pair(2, 1));
	adj[1].push_back(make_pair(5, 3)); adj[1].push_back(make_pair(6, 3));
	adj[2].push_back(make_pair(3, 2));
	adj[3].push_back(make_pair(1, 1)); adj[3].push_back(make_pair(4, 5)); adj[3].push_back(make_pair(5, 3));
	adj[6].push_back(make_pair(5, 2));

	for(const auto i : bellmanFord(0))
		cout << i << " ";
	
	cout << endl;

	return 0;
}
