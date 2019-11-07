// ways-2: edge classification
#include <iostream>
#include <vector>
// #include <algorithm>
using namespace std;

// ͼ����׾����ʾ���� <��ʾ dest �����>
// ��ʼֵΪ -1 (��Ϊ��Ŵ� 0 ��ʼ)
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

// discovered[i] = �� i ������ķ���˳��
// finished[i] = dfs(i)����ֹ�͵��� 1, ������� 0 
vector<int> discovered(adj.size(), -1), finished(adj.size(), 0);
// �ѷ��ֶ���ĸ��� 
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
	
	finished[here] = 1; // �ݹ� 
}

// ����������Ƿ�Ϊ������Ϣ ��ʼ��Ϊ false 
vector<bool> isCutVertex(adj.size(), false);
// discovered<vector>, count(int)

// �Ҵ��� here Ϊ���ڵ�������ĸ��
// ����ֵ�Ǹ��������ܹ�ͨ������ߵ���Ķ����� ���緢�ֵĶ������ʼλ��
// ���ε��� isRoot = true 
int findCutVertex(int here, bool isRoot) {
	// ��¼����˳��
	discovered[here] = counter++;
	int ret = discovered[here];
	// Ϊ���ڶ����Ǹ��ڵ�ʱ�жϸ�� �������ڵ������ĸ���
	int children = 0;
	for(int i=0; i<adj[here].size(); ++i) {
		int there = adj[here][i];
		if(there != -1) {
			if(discovered[there] == -1) {
				children++;
				// ���������ܹ��������߶�������
				int subtree = findCutVertex(there, false);  
				// �����С���������ʱ, ��ǰλ��Ϊ ���
				if( !isRoot && subtree >= discovered[here] )  // �ж�˳���ܸı� 
				// ʵ�ָ��㷨������Ƚϸ���������, ���ǱȽϸ�����ķ���˳�� 
					isCutVertex[here] = true;
				ret = min(ret, subtree);
			} else
	  		  	ret = min(ret, discovered[there]);
		}
	}
	// �����Ǹ��ڵ�ʱ, ͨ�������ĸ����жϴ˶����Ƿ�Ϊ ���
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
