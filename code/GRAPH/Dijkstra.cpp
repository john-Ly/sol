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
// 以有向图为基础 
// 图 邻接表 保存成对(连接的顶点序号, 边线加权值)
vector<pair<int, int> > adj[V];

vector<int> dijkstra_pq(int src) {
	vector<int> dist(V, INF);
	// 默认dist 每个元素的初值应该是 尽可能大 但是<cmath> INF 使用 好像出现问题 手动设置 

	dist[src] = 0;
	priority_queue<pair<int, int> > pq;
	// STL 中的 PQ 按照 i.first 的大小 默认最大堆 (本例采用负数 即 较短的路径 )
	// 所以 first second 的顺序和含义 至关重要 
	// STL:
	// priority_queue<pair<int, int>, vector<pair<int, int>>,
	//				greater<pair<int, int>> > pq;
	// first: the distance to dest
	// second: dest

	pq.push(make_pair(0, src));

	while(!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		// 如果存在比当前取出的路径更短的路径, 那么忽略当前取出的路径
		// 有点类似分支界限 
		if(dist[here] < cost) continue;
		// 检查所有相邻顶点 
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;

			if(dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}
/*
时间消耗两部分:
1. 对各顶点检查边线
   各顶点只检查一次 所以所有边线只检查一次 O(|E|) 
2. 向 pq 添加或删除元素 
   BFS中队列最大长度 O(|V|)
   上述算法在更新 dist[] 会添加 每条边线最大可能都会被添加一次 pq的最大元素个数会是O(|E|) -- 有重复 
   pq添加和删除 O(lg|E|)
   总耗时 O(E lg|E|)
   
   O(|E| + |E|lg|E|) 图结构的顶点个数 |E| 通常会小于 |V|^2 所以 O(lg|E|) =O(lg|V|)
   上述代码时间复杂度  O(E lg|V|)
*/

// 不使用优先级队列: 顶点个数较少或者边线条数很多的时候 速度可能会更快 
vector<int> dijkstra_no_pq(int src) {
	vector<int> dist(V, INF);
	vector<bool> visited(V, false);

	// 该句十分关键 
	dist[src] = 0; //visited[src] = true; BUG!!!

	while(true) {
		int closest = INF, here;
		// 从尚未访问的顶点找出最近的顶点
		for(int i = 0; i<V; ++i) {
			if(dist[i]<closest && !visited[i]) {
				here = i;
				closest = dist[i];
		    }
		}
		cout << here << " " << closest << endl;
		if(closest == INF) break;
		// 访问最近的顶点
		visited[here] = true;
		// 访问最近的顶点的周边 
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i].first;
			if(visited[there]) continue;
			int nextDist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextDist);
		}
	}
	return dist;
}

int main() {
	// pair(连接的顶点序号, 边线加权值)
	adj[0].push_back(make_pair(1, 5)); adj[0].push_back(make_pair(2, 1));
	adj[1].push_back(make_pair(5, 3)); adj[1].push_back(make_pair(6, 3));
	adj[2].push_back(make_pair(3, 2));
	adj[3].push_back(make_pair(1, 1)); adj[3].push_back(make_pair(4, 5)); adj[3].push_back(make_pair(5, 3));
	adj[6].push_back(make_pair(5, 2));

	for(const auto i : dijkstra_pq(0))
		cout << i << " ";
	
	cout << endl;
	for(const auto i : dijkstra_no_pq(0))
		cout << i << " ";

	return 0;
}
