#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ����ͨ�� 

// ͼ����ױ�ʾ����
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

/*  ��ͬ�� DFS �ķ���         @SEE ʵս���� P627 
BFS�� ���ж��㴦������״̬
1. ��δ���ֵ�״̬
2. �ѷ��� ��δ����(���ڶ�����)
3. �ѷ���

O(V^2) �ڽ׾��� 
O(|V|+|E|) �ڽ����� 

*/
// �� start ��ʼ��ͼ���п���������� ������ ���������˳�� 
vector<int> bfs(int start) {
	// �����㷢����� 
	vector<bool> discovered(adj.size(), false);
	// �ѷ��ֶ��� ��δ���ʵ� ����(����Ŀ¼) 
	queue<int> q;
	// �������˳�� 
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
			// ����״������Ķ��� �򱣴浽����Ŀ¼ 
			if(!discovered[there]) {
				q.push(there);
				discovered[there] = true;
			}
		}
	}
	return order;
}

// �� start ��ʼ��ͼ���� BFS --> �����㵽���������·�� + BFS������ 
// distance[i] = start �� i ����̾��� (��¼��㵽 ���е�ľ���) 
// parent[i] = BFS������ �нڵ� i �ĸ��ڵ����, ���ڵ��Ǹ��ڵ�, �����䱾������ 
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

// BFS������ û�б���Ϊһ���������ͼ����̬ �����ø�����ĸ��ڵ���Ž��б�ʾ 
// �Բ�ͬ������� bfs2 �����ɵ� parent[] ��ͬ, �����������������һ��
// ����� v ���������·�� 
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
