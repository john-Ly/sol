#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <utility>  // std::pair
#include <algorithm>
#include <limits>   // numeric_limits
using namespace std;

auto INF = std::numeric_limits<int>::max();
// ������� 
const int V = 4;
// ͼ �ڽӱ� ����ɶ�(���ӵĶ������, ���߼�Ȩֵ)
vector<pair<int, int> > adj[V];
// reachable[u][v] = u �� v ��·�������� ?
bool reachable[V][V];

// ���� src �� target �����·��
// ������ڼ�Ȩֵ���� ��������·��, �򷵻� -INF 
vector<int> bellman2(int src, int target) {
	// ������� ���ж������̾��������Ϊ INF
	vector<int> upper(V, INF);
	upper[src] = 0;
	
	// ���� V-1 ��
	for(int iter=0; iter<V-1; ++iter) {
		for(int here=0; here<V; ++here)
			for(int i=0; i<adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				// �� (here, there) ���߷���
				upper[there] = min(upper[here], upper[here] + cost);
			}
	}
	// ȷ���Ƿ���ڸ�Ȩ��·
	for(int here=0; here<V; ++here)
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			// ����ɳڲ����ɹ� ��ô here �� there ���ڸ�Ȩ��·�� 
			if(upper[there] > upper[here] + cost) {
				// �Ƿ��а����˸�Ȩ��·��·��
				if(reachable[src][here] && reachable[here][target])
					return -INF;
			}
		}
	
	return upper[target];
}

int main() {
	// normal-test
	adj[0].push_back(make_pair(2, -7)); adj[0].push_back(make_pair(3, -4));
	adj[2].push_back(make_pair(1, 3));
	adj[3].push_back(make_pair(2, 9));

	// corner-test
/*	adj[0].push_back(make_pair(1, 4)); adj[0].push_back(make_pair(2, 4));
	adj[2].push_back(make_pair(3, -7));
	adj[3].push_back(make_pair(2, 5));
	adj[4].push_back(make_pair(1, -4)); adj[4].push_back(make_pair(4, -1));*/
	
	return 0;
}
