#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// ͼ����׾����ʾ���� <��ʾ dest �����> --����ͼ 
// ��ʼֵΪ -1 (��Ϊ��Ŵ� 0 ��ʼ)
vector<vector<int> >
adj = { { -1, -1, 2, 3, -1},
	    { 0, -1, -1, -1, -1},
		{ -1, 1, -1, -1, -1},
		{ -1, -1, -1, -1, 4},
		{ -1, -1, -1, -1, -1}
};

// discovered[i] = �� i ������ķ���˳��
// finished[i] = dfs(i)����ֹ�͵��� 1, ������� 0 
vector<int> discovered, finished;

// ������������������� ��Ŵ� 0 ��ʼ
// ����ͬһǿ��ͨ�����ĸ�����������ȫ����ͬ 
vector<int> sccId;
stack<int> st;

int sccCounter, vertexCounter;
// ������ here Ϊ���ڵ�������� �ܹ��������ߵ���С����˳��

// ʵ��ִ������������� 
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;
	// �� here ����ջ��here �����к���ڵ㶼���� here ֮���ջ 
	st.push(here);
	for(int i=0; i<adj[here].size(); ++i) {
		int there = adj[here][i];
		if(there != -1) {
			// (here, there) tree-edge
			if(discovered[there] == -1)
				ret = min( ret, scc(there) );
			// (here, there) forward-edge, ȷ�����Ƚڵ㶥��ķ���˳�� 
		 	else if(discovered[there] < discovered[here]
			 	 && finished[here] != 1)  // �������еĺ���� + �ҳ������ 
	 	        ret = min(ret, discovered[there]);
//////////////////////////// ʵ�ָ��㷨������Ƚϸ���������, ���ǱȽϸ�����ķ���˳�� 
		}
	}
	// �ж� here �Ƿ�Ϊǿ��ͨ�����ĸ��ڵ�
	if(ret == discovered[here]) {
		// �� here Ϊ���ڵ��������, ��ʣ�����ж���ȫ����Ϊͬһ����
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
	// ����ͼ�������ʼ��
	sccId = discovered = finished = vector<int>(adj.size(), -1); 
	sccCounter = vertexCounter = 0;
	// �����ж������ scc()
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
