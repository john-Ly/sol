#include <iostream>
#include <vector>
#include <queue>
#include <map>  // map �е� key ���������кõ� map<vector<int>, int> vector �ܹ��Ƚϴ�С 
#include <algorithm>
#include <cmath>
using namespace std;

// ����ͨ�� 

// instance-1
// Ϊ������ perm ��Ҫִ�з�ת��������ٴ��� 
int sortGame(const vector<int>& perm) {
	int n = perm.size();
	vector<int> sorted = perm;
	// ʵ�ּ���Ŀ�궥�� 
	sort(sorted.begin(), sorted.end());
	
	queue<vector<int> > q;
	map<vector<int>, int> distance;
	
	distance[perm] = 0;
	q.push(perm);
	
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		
		if(here == sorted) return distance[here];
		int cost = distance[here];
		
		// *ʵʱ���ɽṹ����* ----  ʵ������ ���б��ߵ�ȫ����(Permutation)
		// i j �����յ� ����ѭ�� 
		for(int i=0; i<n; ++i)
		    for(int j=i+2; j<=n; ++j) {
		    	// reverse ����ҿ� -- ���� j���� <= n
			    reverse(here.begin()+i, here.begin()+j);
			    // filter for the duplication
			    if(distance.count(here) == 0) {
			    	distance[here] = cost + 1;
			    	q.push(here);
				}
				// for each pass, start the original order
		    	reverse(here.begin()+i, here.begin()+j);
			}
	}
	// error
	return -1;
}

// instance-2
// ״̬�ռ� --- ˫��ͼ 
map<vector<int>, int> toSort;
// �� [0, ..., n-1]������������� toSort[] ������
// Ҫ�����е� ���п��� ���д洢, ��N!�� 
// Ȼ����� "���ֱ���" ��ӳ�� 

// �ȴ洢���еĽ�� -- ��̬�滮�е��Ʊ� 
void precalc(int n) {
	vector<int> perm(n);
	for(int i=0; i<n; ++i)
	    perm[i] = i;
	
	queue<vector<int> > q;
	q.push(perm);
	toSort[perm] = 0;
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int cost = toSort[here];
		
		// ʵʱ���ɽṹ���� 
		for(int i=0; i<n; ++i) {
		    for(int j=i+2; j<=n; ++j) {
			    reverse(here.begin()+i, here.begin()+j);
			    // filter for the duplication
			    if(toSort.count(here) == 0) {
			    	toSort[here] = cost + 1;
			    	q.push(here);
				}
				// for each pass, start the original order
		    	reverse(here.begin()+i, here.begin()+j);
			}
		}
	}
}

int solve(const vector<int>& perm) {
	// ��perm �任�� [0, ..., n-1] 
	int n = perm.size();
	vector<int> fixed(n);
	
	// ����С��ϵ ����ӳ��
	for(int i=0; i<n; ++i) {
		int smaller = 0;
		for(int j=0; j<n; ++j) {
			if(perm[j] < perm[i])
			    ++smaller;
		}
		// �е����Ʋ�������(�ҳ����е�������)---������� �ҳ��ȵ�ǰ�� i С�� 
		fixed[i] = smaller;
		// 0...n-1 ������Ҳ�ǱȽ϶� 
	}
	
	// ӳ��ɹ��� ���
	// binary_search Ч�ʻ���� 
	return toSort[fixed];
}

// instance-3
// ʹ�� ˫�������� -- ��Ϊ״̬�ռ��� ˫��ͼ 
// ���� x �ķ��� 
int sgn(int x) {
	if(!x) return 0;
	return x>0 ? 1 : -1;
}

// ����ֵ+1 
int incr(int x) {
	if(x<0) return x-1;
	return x+1;
}

// distance ��¼ ���е㵽���ľ��� ���Կ���һ����¼�� 
int bidirectional(const vector<int>& perm) {
	int n = perm.size();
	vector<int> sorted = perm;
	sort(sorted.begin(), sorted.end());
	if(perm == sorted) return 0;
	
	queue<vector<int> > q;
	map<vector<int>, int> distance;
	
	q.push(perm); distance[perm] = 1;
	q.push(sorted); distance[sorted] = -1;
	
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		
		int cost = distance[here];
		
		// ʵʱ���ɽṹ���� 
		for(int i=0; i<n; ++i) {
		    for(int j=i+2; j<=n; ++j) {
			    reverse(here.begin()+i, here.begin()+j);
			    // filter for the duplication
			    if(distance.count(here) == 0) {
			    	distance[here] = incr(cost);
			    	q.push(here);
				}
				// ����ʱ (��������������������������� �ʳ�ֵΪ 1)
				else if( sgn(distance[here]) != sgn(cost) )
			        return abs(distance[here]) + abs(cost) - 1;
		    	reverse(here.begin()+i, here.begin()+j);
			}
		}
	}
	// error
	cout << "error" << endl;
	return -1;
}

// instance-4
// Iteratively Deeping Search, IDS
// BFS: �� ���潫Ҫ���ʵĶ����Ŀ¼
// DFS: �����¶����������� ���ᷢ������ռ��̫��ռ� 
// ʹ�� ջ---���ܶ������������ʵĴ����ܶ� ������ջ���������
int best; 
void dfs(vector<int>& start, const vector<int>& finish, int steps) {
    int n = start.size();
	if(steps >= best) return;
	if(start == finish) {
		best = steps; return;
	}

	for(int i=0; i<n; ++i) {
	    for(int j=i+2; j<=n; ++j) {
		    reverse(start.begin()+i, start.begin()+j);
		    dfs(start, finish, steps+1);
		    reverse(start.begin()+i, start.begin()+j);
		}
	}
}

int ids(vector<int>& start, const vector<int>& finish, int growthStep) {
	for(int limit=4; ; limit += growthStep) {
		best = limit + 1;
		dfs(start, finish, 0);
		if(best <= limit)
		    return best;
	}
	return -1;
}

int main() {	
	vector<int> v({3, 4, 1, 2});
//	vector<int> v({1, 2, 3, 4, 8, 7, 6, 5});

    // instance-1 : time-0.03198s
	cout << "BFS:" << endl;
	cout << sortGame(v) << endl;
	
	// instance-2
	cout << "BFS faster version:" << endl;
	precalc(v.size());
	cout << solve(v) << endl;
	
	// instance-3 : time-0.03128s
	cout << "bidirectional:" << endl;
	cout << bidirectional(v) << endl;
	
	// instance-4 : time-0.008558s  time-0.008006s   time-0.00876s
	vector<int> finish(v);
	sort(finish.begin(), finish.end());
	cout << "Iteratively Deepening Search:" << endl;
	cout << ids(v, finish, 2) << endl;

    return 0;
}
