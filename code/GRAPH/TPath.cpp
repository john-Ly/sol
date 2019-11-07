#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// MST(Minimum Spanning Tree) 
// 测试通过 

class DisjSets {
  public:
    explicit DisjSets( int n ) : parent(n), rank(n, 1) {
    	for (int i=0; i<n; ++i)
    		parent[i] = i;
	}

	// path compression + return root
    int find( int u ) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	
	// O(lg N)
    void unionSets( int u, int v ) {
		u = find(u); v = find(v);
		if (u == v) return;
		
		// 保证rank[v] 总是大于 rank[u] --> 将 u 添加为 v 的子节点 
		if(rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
	}

  private:
  	// rank[] 记录每个树的 阶 
    vector<int> parent, rank;
};

const int MAX_V = 100;
const int INF = 987654321;
// 顶点个数 
int V = 7;
// 图 邻接表 保存成对(连接的顶点序号, 边线加权值)
vector<pair<int, int> > adj[MAX_V];

// 对给出的图结构 将最小生成树的边线目录保存到 selected
// 并返回加权值之和
// 
// 并查集运算与常数时间相等
// 边线排序时间： O(|E| lg |E|) 
int kruskal(vector<pair<int, int> >& selected) {
	int ret = 0;
	selected.clear();
	// 求(加权值, (顶点-1, 顶点-2))的目录
	vector< pair<int, pair<int, int> > > edges;
	
	// u: here v: there 
	for(int u=0; u<V; ++u)
		for(int i=0; i<adj[u].size(); ++i) {
			int v = adj[u][i].first;
			int cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}

	// 按照加权值大小排序 从小到大 升序
	sort(edges.begin(), edges.end());
	// 刚开始 所有顶点相互分离
	DisjSets sets(V);
	for(int i=0; i<edges.size(); ++i) {
		// 检查边线(u, v)
		int cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		// 忽略 u 和 v 已连接的情况 -- 即回路 
		if(sets.find(u) == sets.find(v)) continue;
		// 合并 u 和 v
		sets.unionSets(u, v);
		selected.push_back(make_pair(u, v));
		ret += cost; 
	}
	return ret;
}


// 对给出的图结构 将最小生成树的边线目录保存到 selected
// 并返回加权值之和
//
// O(|V|^2 + |E|)
int prim(vector<pair<int, int> >& selected) {
	int ret = 0;
	// 相应顶点是否已包含到生成树结构 
	vector<bool> added(V, false);
	// 保存树结构相邻边线中连接到相应顶点的最小边线的信息 
	vector<int> minWeight(V, INF), parent(V, -1);

	minWeight[0] = parent[0] = 0;
	for(int iter=0; iter<V; ++iter) {
		// 找出下一个要添加到树结构的顶点 u (在树结构集合 和 剩余未选中的结点 中确定)
		int u = -1;  // u == -1 为了让程序起始(u=0 的情况允许被添加) 
		for(int v=0; v<V; ++v)
			if(!added[v] && ((u == -1)|| minWeight[u] > minWeight[v]))
				u = v;
		// 时间复杂度 : O(|V|) 

		// 把(parent[u], u)添加到树结构
		if(parent[u] != u)
			selected.push_back(make_pair(parent[u], u));
		ret += minWeight[u];
		added[u] = true;
		
		// 当添加了新节点后 -- 选出最小权值的边线 
		// 检查 u 的相邻边线(u, v)
		for(int i=0; i<adj[u].size(); ++i) {
			int v = adj[u][i].first, weight = adj[u][i].second;
			if(!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
				// 此处会维护 minWeight[] 数组 
			}
		}
	}
	return ret;
}

int main() {
	// MST 无向连通图 
	adj[0].push_back(make_pair(1, 5)); adj[0].push_back(make_pair(2, 1));
	adj[1].push_back(make_pair(5, 3)); adj[1].push_back(make_pair(6, 3)); adj[1].push_back(make_pair(0, 5)); adj[1].push_back(make_pair(3, 1));
	adj[2].push_back(make_pair(0, 1)); adj[2].push_back(make_pair(3, 4));
	adj[3].push_back(make_pair(1, 1)); adj[3].push_back(make_pair(4, 5)); adj[3].push_back(make_pair(5, 3)); adj[3].push_back(make_pair(2, 4));
	adj[4].push_back(make_pair(3, 5));
	adj[5].push_back(make_pair(1, 3)); adj[5].push_back(make_pair(6, 2)); adj[5].push_back(make_pair(3, 3));
	adj[6].push_back(make_pair(5, 2)); adj[6].push_back(make_pair(1, 3));

	vector<pair<int, int> > tmp;
	cout << kruskal(tmp) << endl;
	for(const auto i : tmp)
		cout << i.first << " " << i.second << endl;
	// 最小生成树也有多种情况 
	tmp.clear();
	cout << prim(tmp) << endl;
	for(const auto i : tmp)
		cout << i.first << " " << i.second << endl;	

	return 0;
}
