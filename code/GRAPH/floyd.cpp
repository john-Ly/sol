#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ������� 
const int V = 7;
// ͼ �ڽӾ���
// adj[u][v] = �� u �� v �ı���Ȩֵ ��û�б���, �ʹ��뼫��ֵ 
int adj[V][V];
int C[V][V][V];
// Ck(u, v) = ֻ�� 0�� k �Ķ�������;����ʱ, �õ��Ĵ� u�� v����̾��� 

void allPairShortestPath1() {
	// ��ʼ�� C[0]
	for(int i=0; i<V; ++i)
		for(int j=0; j<V; ++j)
			if(i != j)
	 			C[0][i][j] = min(adj[i][j], adj[i][0]+adj[0][j]);
			else
				C[0][i][j] = 0;
	// ���� C[k-1]  ������� C[k]
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

