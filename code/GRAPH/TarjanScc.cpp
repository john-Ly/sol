#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 图的领阶矩阵表示方法 <表示 dest 的序号> --有向图 
// 初始值为 -1 (因为编号从 0 开始)
vector<vector<int> >
adj = { { -1, -1, 2, 3, -1},
	    { 0, -1, -1, -1, -1},
		{ -1, 1, -1, -1, -1},
		{ -1, -1, -1, -1, 4},
		{ -1, -1, -1, -1, -1}
};

// discovered[i] = 第 i 个顶点的发现顺序
// finished[i] = dfs(i)已终止就等于 1, 否则等于 0 
vector<int> discovered, finished;

// 各顶点所属分量的序号 序号从 0 起始
// 属于同一强连通分量的各顶点分量序号全部相同 
vector<int> sccId;
stack<int> st;

int sccCounter, vertexCounter;
// 返回以 here 为根节点的子树中 能够到达后向边的最小发现顺序

// 实际执行深度优先搜索 
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;
	// 将 here 存入栈。here 的所有后代节点都会在 here 之后进栈 
	st.push(here);
	for(int i=0; i<adj[here].size(); ++i) {
		int there = adj[here][i];
		if(there != -1) {
			// (here, there) tree-edge
			if(discovered[there] == -1)
				ret = min( ret, scc(there) );
			// (here, there) forward-edge, 确认祖先节点顶点的发现顺序 
		 	else if(discovered[there] < discovered[here]
			 	 && finished[here] != 1)  // 忽略所有的横向边 + 找出后向边 
	 	        ret = min(ret, discovered[there]);
//////////////////////////// 实现该算法并不会比较各顶点的深度, 而是比较各顶点的发现顺序 
		}
	}
	// 判断 here 是否为强连通分量的根节点
	if(ret == discovered[here]) {
		// 以 here 为根节点的子树中, 将剩余所有顶点全部绑定为同一分量
		while(true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if(t == here) break;
		}
		++sccCounter;
	} 
 
	finished[here] = 1;
	return ret;
}

// Tarjan SCC
vector<int> tarjanSCC() {
	// 数组和计数器初始化
	sccId = discovered = finished = vector<int>(adj.size(), -1); 
	sccCounter = vertexCounter = 0;
	// 对所有顶点调用 scc()
	for(int i=0; i<adj.size(); ++i)
		if(discovered[i] == -1) scc(i);
	return sccId;
}


int main () {
	vector<int> tmp = tarjanSCC();
	for(auto i : tmp)
 		cout << i << " ";
	
	return 0; 
} 
