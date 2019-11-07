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
const int V = 7;
// ͼ �ڽӱ� ����ɶ�(���ӵĶ������, ���߼�Ȩֵ)
vector<pair<int, int> > adj[V];

// O(|V||E|) 
// ������ڸ�Ȩ��·, �򷵻ؿ����� 
vector<int> bellmanFord(int src) {
	// ������� ���ж������̾��������Ϊ INF
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;
	
	// ���� V ��
	for(int iter=0; iter<V; ++iter) {
		updated = false;
		// ���� for ѭ�� �������б����ɳ� 
		for(int here=0; here<V; ++here)
			for(int i=0; i<adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
									cout << there << "=========" << here << endl;
					cout << upper[there] << " " << upper[here] << " " << cost << endl;
				// ������ (here, there) ���߷���
				if(upper[there] > upper[here] + cost) {
					// �ɹ�
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
			
		// �����б����ɳڲ�����ʧ�ܺ�, û�б�Ҫѭ�� V-1 �� ֱ����ֹ
		if(!updated) break; 
	}
	// �� V �α����ɹ�ִ�����ɳڲ��� �ض����ڸ�Ȩ��·
	if(updated) upper.clear();
	
	return upper;
}

int main() {
	adj[0].push_back(make_pair(1, 5)); adj[0].push_back(make_pair(2, 1));
	adj[1].push_back(make_pair(5, 3)); adj[1].push_back(make_pair(6, 3));
	adj[2].push_back(make_pair(3, 2));
	adj[3].push_back(make_pair(1, 1)); adj[3].push_back(make_pair(4, 5)); adj[3].push_back(make_pair(5, 3));
	adj[6].push_back(make_pair(5, 2));

	for(const auto i : bellmanFord(0))
		cout << i << " ";
	
	cout << endl;

	return 0;
}
