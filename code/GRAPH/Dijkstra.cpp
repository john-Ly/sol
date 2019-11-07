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
// ������ͼΪ���� 
// ͼ �ڽӱ� ����ɶ�(���ӵĶ������, ���߼�Ȩֵ)
vector<pair<int, int> > adj[V];

vector<int> dijkstra_pq(int src) {
	vector<int> dist(V, INF);
	// Ĭ��dist ÿ��Ԫ�صĳ�ֵӦ���� �����ܴ� ����<cmath> INF ʹ�� ����������� �ֶ����� 

	dist[src] = 0;
	priority_queue<pair<int, int> > pq;
	// STL �е� PQ ���� i.first �Ĵ�С Ĭ������ (�������ø��� �� �϶̵�·�� )
	// ���� first second ��˳��ͺ��� ������Ҫ 
	// STL:
	// priority_queue<pair<int, int>, vector<pair<int, int>>,
	//				greater<pair<int, int>> > pq;
	// first: the distance to dest
	// second: dest

	pq.push(make_pair(0, src));

	while(!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		// ������ڱȵ�ǰȡ����·�����̵�·��, ��ô���Ե�ǰȡ����·��
		// �е����Ʒ�֧���� 
		if(dist[here] < cost) continue;
		// ����������ڶ��� 
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;

			if(dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}
/*
ʱ������������:
1. �Ը����������
   ������ֻ���һ�� �������б���ֻ���һ�� O(|E|) 
2. �� pq ��ӻ�ɾ��Ԫ�� 
   BFS�ж�����󳤶� O(|V|)
   �����㷨�ڸ��� dist[] ����� ÿ�����������ܶ��ᱻ���һ�� pq�����Ԫ�ظ�������O(|E|) -- ���ظ� 
   pq��Ӻ�ɾ�� O(lg|E|)
   �ܺ�ʱ O(E lg|E|)
   
   O(|E| + |E|lg|E|) ͼ�ṹ�Ķ������ |E| ͨ����С�� |V|^2 ���� O(lg|E|) =O(lg|V|)
   ��������ʱ�临�Ӷ�  O(E lg|V|)
*/

// ��ʹ�����ȼ�����: ����������ٻ��߱��������ܶ��ʱ�� �ٶȿ��ܻ���� 
vector<int> dijkstra_no_pq(int src) {
	vector<int> dist(V, INF);
	vector<bool> visited(V, false);

	// �þ�ʮ�ֹؼ� 
	dist[src] = 0; //visited[src] = true; BUG!!!

	while(true) {
		int closest = INF, here;
		// ����δ���ʵĶ����ҳ�����Ķ���
		for(int i = 0; i<V; ++i) {
			if(dist[i]<closest && !visited[i]) {
				here = i;
				closest = dist[i];
		    }
		}
		cout << here << " " << closest << endl;
		if(closest == INF) break;
		// ��������Ķ���
		visited[here] = true;
		// ��������Ķ�����ܱ� 
		for(int i=0; i<adj[here].size(); ++i) {
			int there = adj[here][i].first;
			if(visited[there]) continue;
			int nextDist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextDist);
		}
	}
	return dist;
}

int main() {
	// pair(���ӵĶ������, ���߼�Ȩֵ)
	adj[0].push_back(make_pair(1, 5)); adj[0].push_back(make_pair(2, 1));
	adj[1].push_back(make_pair(5, 3)); adj[1].push_back(make_pair(6, 3));
	adj[2].push_back(make_pair(3, 2));
	adj[3].push_back(make_pair(1, 1)); adj[3].push_back(make_pair(4, 5)); adj[3].push_back(make_pair(5, 3));
	adj[6].push_back(make_pair(5, 2));

	for(const auto i : dijkstra_pq(0))
		cout << i << " ";
	
	cout << endl;
	for(const auto i : dijkstra_no_pq(0))
		cout << i << " ";

	return 0;
}
