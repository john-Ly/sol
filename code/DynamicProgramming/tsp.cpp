#include <iostream>
#include <vector>
#include <algorithm>  // max, sort
#include <utility>  // pair
#include <cstring> // memset()
using namespace std;
// �뺺��ε���һ����Ŀ ������
// �������� ��������ѡ��·�� 
// δ��ɣ��������������� 

const int INF = 987654321;

int n; // ���и���
double dist[MAX][MAX];  // ���Ǽ��
// path: �Ѽ�����·�� 
// visited: �Ը����з������ 
// currentLength: �����Ѽ���·���ĳ��� 
// �ڷ�������ʣ����е�·���� �������·��
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	// ���Բ��� ���г��ж��ѷ������ ��ص���ʼ���� ��ֹ���� 
	if(path.size() == n)
        return currentLength + dist[path[0]][path.back()];
	
	double ret = INF;
	// �������п��ܵ���һ��Ҫ���ʵĳ���
	for(int next=0; next<n; ++next) {
		if(visited[next]) continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;
		// ���õݹ�������ʣ��·���ļ��� ���ó����·���ĳ���
		double cand = shortestPath(path, visited, currentLength+dist[here][next]);
		ret = min(ret, cand);
		
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}

double cache[MAX][1<<MAX];
double shortestPath(int here, int visited) {
	// �� 0 �յ���� 
	if(visited == (1<<n)-1 ) return dist[here][0];
	
	double& ret = cache[here][visited];
	if(ret >= 0) return ret;
	
	ret = INF;
	// ��������Ҫ���ʵ���һ������ 
	for(int there=0; there<n; ++there) {
		if(visited & (1<<n) ) continue;
		double cand = dist[here][next] + shortestPath2(next, visited+(1<<next));
		ret = min(ret, cand);
	}
    return ret;
}

int main() {
	memset(cache, -1, sizeof(cache));
    vector<int> tmp;
    p = 0; tmp.push_back(p);
    day = 2; q = 4; n = 5;
	 
	double probability = search(tmp);
    cout << probability << endl;
    cout << search2(p, day) << endl;

    return 0;
}
