#include "BipartiteDisjoint.h"
#include <algorithm>

// reuse parent[] is not good
int BipartiteDisjoint::find()
{
    if( parent[ u ] < 0 )
   		return u;
	return parent[u] = find( parent[u] );
}

int BipartiteDisjoint::unionSets(int u, int v)
{
	if(u == -1 || v == -1) return std::max(u, v);
	
	u = find(u); v = find(v);
	if(u == v) return;
	
	if( parent[u] < parent[v]) // the height of v is grater than u (while using negative number)
		swap(u,v);
		
	if( parent[u] == parent[v]) --parent[v];
	parent[u] = v;
	size[v] += size[u];
}

bool BipartiteDisjoint::dis(int u, int v)
{
	u = find(u); v = find(v);
	if(u == v)  // u , v can't locate the same set
        return false;
 
	// enemy's enemy is friend
	int a = unionSets(u, enemy[v]), b = unionSets(v, enemy[u]);
	enemy[a] = b; enemy[b] = a;
	return true;
}

bool BipartiteDisjoint::ack(int u, int v)
{
	u = find(u); v = find(v);
	if(enemy[u] == v)  // u , v are enemy
        return false;
 
	// freind's enemy is enemy
	int a = unionSets(u, v), b = unionSets(enemey[v], enemy[u]);
	enemy[a] = b;
	if(b != -1)
  	 	 enemy[b] = a;
	
	return true;
}
