#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// MST(Minimum Spanning Tree) 
// ����ͨ�� 

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
		
		// ��֤rank[v] ���Ǵ��� rank[u] --> �� u ���Ϊ v ���ӽڵ� 
		if(rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
	}

  private:
  	// rank[] ��¼ÿ������ �� 
    vector<int> parent, rank;
};

const int MAX_V = 100;
const int INF = 987654321;
// ������� 
int V = 7;
// ͼ �ڽӱ� ����ɶ�(���ӵĶ������, ���߼�Ȩֵ)
vector<pair<int, int> > adj[MAX_V];

// �Ը�����ͼ�ṹ ����С�������ı���Ŀ¼���浽 selected
// �����ؼ�Ȩֵ֮��
// 
// ���鼯�����볣��ʱ�����
// ��������ʱ�䣺 O(|E| lg |E|) 
int kruskal(vector<pair<int, int> >& selected) {
	int ret = 0;
	selected.clear();
	// ��(��Ȩֵ, (����-1, ����-2))��Ŀ¼
	vector< pair<int, pair<int, int> > > edges;
	
	// u: here v: there 
	for(int u=0; u<V; ++u)
		for(int i=0; i<adj[u].size(); ++i) {
			int v = adj[u][i].first;
			int cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}

	// ���ռ�Ȩֵ��С���� ��С���� ����
	sort(edges.begin(), edges.end());
	// �տ�ʼ ���ж����໥����
	DisjSets sets(V);
	for(int i=0; i<edges.size(); ++i) {
		// ������(u, v)
		int cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		// ���� u �� v �����ӵ���� -- ����· 
		if(sets.find(u) == sets.find(v)) continue;
		// �ϲ� u �� v
		sets.unionSets(u, v);
		selected.push_back(make_pair(u, v));
		ret += cost; 
	}
	return ret;
}


// �Ը�����ͼ�ṹ ����С�������ı���Ŀ¼���浽 selected
// �����ؼ�Ȩֵ֮��
//
// O(|V|^2 + |E|)
int prim(vector<pair<int, int> >& selected) {
	int ret = 0;
	// ��Ӧ�����Ƿ��Ѱ������������ṹ 
	vector<bool> added(V, false);
	// �������ṹ���ڱ��������ӵ���Ӧ�������С���ߵ���Ϣ 
	vector<int> minWeight(V, INF), parent(V, -1);

	minWeight[0] = parent[0] = 0;
	for(int iter=0; iter<V; ++iter) {
		// �ҳ���һ��Ҫ��ӵ����ṹ�Ķ��� u (�����ṹ���� �� ʣ��δѡ�еĽ�� ��ȷ��)
		int u = -1;  // u == -1 Ϊ���ó�����ʼ(u=0 ������������) 
		for(int v=0; v<V; ++v)
			if(!added[v] && ((u == -1)|| minWeight[u] > minWeight[v]))
				u = v;
		// ʱ�临�Ӷ� : O(|V|) 

		// ��(parent[u], u)��ӵ����ṹ
		if(parent[u] != u)
			selected.push_back(make_pair(parent[u], u));
		ret += minWeight[u];
		added[u] = true;
		
		// ��������½ڵ�� -- ѡ����СȨֵ�ı��� 
		// ��� u �����ڱ���(u, v)
		for(int i=0; i<adj[u].size(); ++i) {
			int v = adj[u][i].first, weight = adj[u][i].second;
			if(!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
				// �˴���ά�� minWeight[] ���� 
			}
		}
	}
	return ret;
}

int main() {
	// MST ������ͨͼ 
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
	// ��С������Ҳ�ж������ 
	tmp.clear();
	cout << prim(tmp) << endl;
	for(const auto i : tmp)
		cout << i.first << " " << i.second << endl;	

	return 0;
}
