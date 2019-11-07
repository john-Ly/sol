#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 测试通过 

// 图的领阶表示方法
vector<vector<int> >
adj = { {1, 3, 4, 7},
	    {0, 2, 3},
	    {1, 5, 6},
	    {0, 1, 6},
	    {0, 5},
	    {2, 4},
	    {2, 3, 8},
	    {0},
	    {6}
};

/*  不同与 DFS 的访问         @SEE 实战策略 P627 
BFS中 所有顶点处于三种状态
1. 尚未发现的状态
2. 已发现 但未访问(存在队列中)
3. 已访问

O(V^2) 邻阶矩阵 
O(|V|+|E|) 邻接链表 

*/
// 从 start 起始对图进行宽度优先搜索 并返回 各顶点访问顺序 
vector<int> bfs(int start) {
	// 各顶点发现与否 
	vector<bool> discovered(adj.size(), false);
	// 已发现顶点 尚未访问的 队列(顶点目录) 
	queue<int> q;
	// 顶点访问顺序 
	vector<int> order;
	discovered[start] = true;
	q.push(start);
	while(!q.empty()) {
		int here = q.front();
		q.pop();
		// access here
		order.push_back(here);
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i];
			// 如果首次遇到的顶点 则保存到发现目录 
			if(!discovered[there]) {
				q.push(there);
				discovered[there] = true;
			}
		}
	}
	return order;
}

// 从 start 起始对图进行 BFS --> 求出起点到各顶点最短路径 + BFS生成树 
// distance[i] = start 到 i 的最短距离 (记录起点到 所有点的距离) 
// parent[i] = BFS生成树 中节点 i 的父节点序号, 若节点是根节点, 则是其本身的序号 
void bfs2(int start, vector<int>& distance, vector<int>& parent) {
	distance = vector<int>(adj.size(), -1);
	parent = vector<int>(adj.size(), -1);
	
	queue<int> q;
	distance[start] = 0;
	parent[start] = start;
	q.push(start);
	
	while(!q.empty()) {
		int here = q.front();
		q.pop();
		
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i];
			if(distance[there] == -1) {
				q.push(there);
				distance[there] = distance[here] + 1;
				parent[there] = here;
			}
		}
	}
}

// BFS生成树 没有保存为一般的树或者图的形态 而是用个顶点的父节点序号进行表示 
// 以不同的起点在 bfs2 中生成的 parent[] 不同, 故深度搜索生成树不一样
// 计算从 v 到起点的最短路径 
vector<int> shortestPath(int v, const vector<int>& parent) {
	vector<int> path(1, v);
	while(parent[v] != v) {
		v = parent[v];
		path.push_back(v);
	}
	
	reverse(path.begin(), path.end());
	return path;
}

int main() { 
	vector<int> distance, parent;
	 
	cout << "access order:\n";
	for(auto i: bfs(0))
 		cout << i << " ";
 	cout << endl;
	////////////////////////////////////////////
	bfs2(0, distance, parent);
	cout << "distance to vertex 0:\n";
	for(auto i: distance)
 		cout << i << " ";
 	cout << endl;
 	
	cout << "parent:\n";
	for(auto i: parent)
 		cout << i << " ";
 	cout << endl;
	
	cout << "shortest distance 0-2:\n";
	for( auto i: shortestPath(2, parent) )
 		cout << i << " ";

    return 0;
}
