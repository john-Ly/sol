#include <vector>
#include <algorithm>
using namespace std;

// union-find 需要把原始数据进行映射, 只是一个划分集合的数据结构
// @TODO leetcode 右两个专题
class DisjSets {
  public:
    explicit DisjSets( int n ) : parent(n), rank(n, 1) {
    	for (int i=0; i<n; ++i)
    		parent[i] = i;
	}

    // Return set containing u
	// path compression + return root
    // return find(parent[u])  can avoid repeat computation
    int find( int u ) const {
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
    // union-by-rank
    vector<int> parent, rank;
};


int main() {

    return 0;
}