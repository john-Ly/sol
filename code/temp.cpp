#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int N, illpair;
string com, tmp;
map<char, int> m;

struct BipartiteDisjoint
{
	public:
		explicit BipartiteDisjoint( int n )
		: parent(n, -1), size(n, 1), enemy(n, -1) { }
	    
		int find( int u ) {
			if( parent[ u ] < 0 )
				return u;
			return parent[u] = find( parent[u] );
		}

	    int unionSets( int u, int v ) {
	    	if(u == -1 || v == -1) return std::max(u, v);
	
			u = find(u); v = find(v);
			if(u == v) return u;
			
			if( parent[u] < parent[v])
				swap(u,v);
				
			if( parent[u] == parent[v]) --parent[v];
			parent[u] = v;
			size[v] += size[u];
			
			return v;
		}
	    

	    bool dis(int u, int v) {
	    	u = find(u); v = find(v);
			if(u == v)
		        return false;
 

			int a = unionSets(u, enemy[v]), b = unionSets(v, enemy[u]);
			enemy[a] = b; enemy[b] = a;
			return true;
		}
		
    vector<int> parent, size, enemy;
};

void preProcess(vector<pair<int, int> >& v) {
	for(int i=0; i<illpair; ++i) {
		cin >> tmp;
		v.push_back(make_pair( m[*tmp.begin()], m[*tmp.end()] ) );
	}
}

int maxLeft(BipartiteDisjoint& buf){
	int ret = 0;
	for(int i=0; i<N; ++i){
		if(buf.find(i) == i) {
			int enemy = buf.enemy[i];
			if(enemy > i) continue;
			int Size = buf.size[i];
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
			ret += max(Size, enemySize);
		}
	}
	return ret;
}


int main() {
	while(cin >> N >> com >> illpair) {
		int j =0;
		for(auto i: com) {
			m[i] = j;
			++j;
		}

		vector<pair<int, int> > store;
		preProcess(store);
		BipartiteDisjoint ds(N);
		for(auto i : store) {
			ds.dis(i.first, i.second);
		}
		
		cout << N - maxLeft(ds) + 1 << endl;

	}
	
	return 0;
}
