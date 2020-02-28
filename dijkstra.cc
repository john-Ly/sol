#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <utility>  // std::pair
#include <algorithm>
#include <limits>   // numeric_limits
using namespace std;

namespace bfs_w_same {
// 针对权重相同的图 -- 路径即两点之间 edge 的个数
// 从 start 起始对图进行 BFS --> 求出起点到各顶点最短路径 + BFS生成树
// distance[i] = start 到 i 的最短距离 (记录起点到 所有点的距离)
// parent[i] = BFS生成树 中节点 i 的父节点序号, 若节点是根节点, 则是其本身的序号
void bfs2(int start, vector<int>& distance, vector<int>& parent) {
	distance = vector<int>(adj.size(), -1);
	// parent = vector<int>(adj.size(), -1);

	queue<int> q;
	distance[start] = 0;
	// parent[start] = start;
	q.push(start);

	while(!q.empty()) {
		int here = q.front();
		q.pop();

		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i];
			if(distance[there] == -1) {
				q.push(there);
                // dist[v] = dist[u] + 1  ; dist 表示节点到根节点的距离
				distance[there] = distance[here] + 1;
				// parent[there] = here;
			}
		}
	}
}
}


auto INF = std::numeric_limits<int>::max();
// 顶点个数
constexpr int V = 7;
// 以有向图为基础
// 图 邻接表 保存成对(连接的顶点序号, 边线加权值)
vector<pair<int, int> > adj[V];
vector<int> parent(V, -1);  // 生成最短路径

// dijstra不能对负权边进行正确处理
vector<int> dijkstra_pq(int src) {
	vector<int> dist(V, INF);
	// 默认dist 每个元素的初值应该是 尽可能大 但是<cmath> INF 使用 好像出现问题 手动设置

	dist[src] = 0;
    parent[src] = src;
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
        // cout << pq.size() << '\n';
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		// 如果存在比当前取出的路径更短的路径, 那么忽略当前取出的路径
		// 有点类似分支界限
		if(dist[here] < cost) continue;
		// 检查所有相邻顶点
		for(int i=0; i<adj[here].size(); ++i) {

			int there = adj[here][i].first;
            //  dist[v]  dist[u] + w(u, v)
			int nextDist = cost + adj[here][i].second;

            // 更新最短距离 dist
			if(dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
                parent[there] = here;
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

vector<int> shortestPath(int v) {
	vector<int> path(1, v);
	while(parent[v] != v) {
		v = parent[v];
		path.push_back(v);
	}

	reverse(path.begin(), path.end());
	return path;
}

/*
0 0
0-2147483647-2147483647-2147483647-2147483647-2147483647-2147483647-
2 1
0-5-1-2147483647-2147483647-2147483647-2147483647-
3 3
0-5-1-3-2147483647-2147483647-2147483647-
1 4
0-4-1-3-8-6-2147483647-
5 6
0-4-1-3-8-6-7-
6 7
0-4-1-3-8-6-7-
4 8
0-4-1-3-8-6-7-
4 2147483647
0-4-1-3-8-6-7-
0 4 1 3 8 6 7
*/
// 不使用优先级队列: 顶点个数较少或者边线条数很多的时候 速度可能会更快
vector<int> dijkstra_no_pq(int src) {
	vector<int> dist(V, INF);
	vector<bool> visited(V, false);

	// 该句十分关键
	dist[src] = 0; //visited[src] = true; BUG!!!

	while(true) {
        // closest 每个loop都会更新
		int closest = INF, here;

		// 从尚未访问的顶点 找出最小的dist[]
		for(int i = 0; i<V; ++i) {
			if(dist[i]<closest && !visited[i]) {
				here = i;
				closest = dist[i];
		    }
		}

		// cout << here << ':' << closest << endl;
        // for (auto i : dist) cout << i << '-';
        // cout << '\n';

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
    // 有向图
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

	cout << "\nshortest distance a->b:\n";
	for( auto i: shortestPath(1) )
 		cout << i << " ";

	cout << "\nshortest distance a->g:\n";
	for( auto i: shortestPath(6) )
 		cout << i << " ";

	return 0;
}
