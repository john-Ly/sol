#ifndef BIPARTITEDISJOINT_H
#define BIPARTITEDISJOINT_H

#include <vector>
using namespace std;

class BipartiteDisjoint
{
	public:
		explicit BipartiteDisjoint( int n )
		: parent(n, -1), size(n, 1), enemy(n, -1)
	    
		int find( int u );
		// Use union by rank and path compression.
	    int unionSets( int u, int v );
	    
	    // u, v are enemy
	    bool dis(int u, int v);
  		// u, v are friend
	    bool ack(int u, int v);

  private:
  	// parent[i] the root has the rank(height info)
	// size[i] record the size of the set when it's root
	// enemy[i] record the the root of the enemy's set
	//           default value is -1--means no enemy find
    vector<int> parent, size, enemy;
};

#endif
