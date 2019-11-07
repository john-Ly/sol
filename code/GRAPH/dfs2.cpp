// ways-2: edge classification
#include <iostream>
#include <vector>
// #include <algorithm>
using namespace std;

// 图的领阶矩阵表示方法 <表示 dest 的序号>
// 初始值为 -1 (因为编号从 0 开始)
vector<vector<int> >
// edge-classification 
adj = { { -1, 1, 2, 3},
	    { -1, -1, 2, -1},
		{ -1, 1, -1, -1},
		{ -1, 1, 2, -1},
};

// find cut-vertex 
/*
adj = { { -1, 1, -1, -1, -1, -1, -1, -1},
	    { 0, -1, 2, 3, -1, -1, -1, -1},
		{ -1, 1, -1, 3, -1, 5, -1, -1},
		{ -1, 1, 2, -1, 4, 5, -1, -1},
		{ -1, -1, -1, 3, -1, -1, -1, -1},
		{ -1, -1, 2, 3, -1, -1, 6, 7},
		{ -1, -1, -1, -1, -1, 5, -1, -1},
		{ -1, -1, -1, -1, -1, 5, -1, -1}
};
*/

// discovered[i] = 第 i 个顶点的发现顺序
// finished[i] = dfs(i)已终止就等于 1, 否则等于 0 
vector<int> discovered(adj.size(), -1), finished(adj.size(), 0);
// 已发现顶点的个数 
int counter = 0;

void dfs2(int here) {
	discovered[here] = counter++;
	for(int i=0; i<adj[here].size(); ++i) {
		int there = adj[here][i];
		if(there != -1) {
			cout << "(" << here << "," << there << ") is a ";
			if(discovered[there] == -1) {
				cout << "tree edge" << endl;
				dfs2(there);
			}
		 	else if(discovered[here] < discovered[there])
	 	        cout << "forward edge" << endl;
		    else if(finished[there] == 0)
	            cout << "back edge" << endl;
	        else
	            cout << "cross edge" << endl;
		}
	}
	
	finished[here] = 1; // 递归 
}

// 保存各顶点是否为割点的信息 初始化为 false 
vector<bool> isCutVertex(adj.size(), false);
// discovered<vector>, count(int)

// 找处以 here 为根节点的子树的割点
// 返回值是该子树中能够通过后向边到达的顶点中 最早发现的顶点的起始位置
// 初次调用 isRoot = true 
int findCutVertex(int here, bool isRoot) {
	// 记录发现顺序
	discovered[here] = counter++;
	int ret = discovered[here];
	// 为了在顶点是根节点时判断割点 计算后代节点子树的个数
	int children = 0;
	for(int i=0; i<adj[here].size(); ++i) {
		int there = adj[here][i];
		if(there != -1) {
			if(discovered[there] == -1) {
				children++;
				// 此子树中能够到达的最高顶点的序号
				int subtree = findCutVertex(there, false);  
				// 该序号小于自身序号时, 当前位置为 割点
				if( !isRoot && subtree >= discovered[here] )  // 判定顺序不能改变 
				// 实现该算法并不会比较各顶点的深度, 而是比较各顶点的发现顺序 
					isCutVertex[here] = true;
				ret = min(ret, subtree);
			} else
	  		  	ret = min(ret, discovered[there]);
		}
	}
	// 顶点是根节点时, 通过子树的个数判断此顶点是否为 割点
	if(isRoot) isCutVertex[here] = (children >= 2 );
	return ret;
}

int main () {
	dfs2(0);  // directional is diff

	/*
	(0,1) is a tree edge
	(1,2) is a tree edge
	(2,1) is a back edge
	(0,2) is a forward edge
	(0,3) is a tree edge
	(3,1) is a cross edge
	(3,2) is a cross edge
	*/
	
	/*
	int tmp = findCutVertex(0, true);
	for(int i=0; i<adj.size(); i++) {
		if(isCutVertex[i])
			cout << i << " ";
	}
	*/ 
	
	return 0; 
} 
