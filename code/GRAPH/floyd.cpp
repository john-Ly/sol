#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 顶点个数 
const int V = 7;
// 图 邻接矩阵
// adj[u][v] = 从 u 到 v 的边线权值 若没有边线, 就代入极大值 
int adj[V][V];
int C[V][V][V];
// Ck(u, v) = 只把 0到 k 的顶点用作途经点时, 得到的从 u到 v的最短距离 

void allPairShortestPath1() {
	// 初始化 C[0]
	for(int i=0; i<V; ++i)
		for(int j=0; j<V; ++j)
			if(i != j)
	 			C[0][i][j] = min(adj[i][j], adj[i][0]+adj[0][j]);
			else
				C[0][i][j] = 0;
	// 若有 C[k-1]  则能算出 C[k]
	for(int k=1; k<V; ++k)
		for(int i=0; i<V; ++i)
			for(int j=0; j<V; ++j)
	 			C[k][i][j] = min( C[k-1][i][j],
				 	C[k-1][i][k] + C[k-1][k][j] );
}

void floyd() {
	for(int k=1; k<V; ++k)
		adj[k][k] = 0;	
	for(int k=1; k<V; ++k)
		for(int i=0; i<V; ++i)
			for(int j=0; j<V; ++j)
	 			adj[i][j] = min( adj[i][j],
				 	adj[i][k] + adj[k][j] );
}

