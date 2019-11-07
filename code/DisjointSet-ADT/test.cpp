#include <iostream>
#include <vector>
using namespace std;

// use parent[] store the rank of the root, save some space
// just for test, lack of general purpose

class DisjSets
{
  public:
    explicit DisjSets( int numElements ) : parent(numElements, -1)
	{}

    int find( int u ) {  // path compression
	    if( parent[ u ] < 0 )
	        return u;
    	return parent[u] = find( parent[u] );
	}
	
    void unionSets( int u, int v) { // union by rank & let v's clique become the root.
    	u = find(u); v = find(v);
    	if(u == v) return;
    	
    	if( parent[u] < parent[v]) // the height of v is grater than u (while using negative number)
			swap(u,v);
			
    	if( parent[u] == parent[v]) --parent[v];
    	parent[u] = v;
	}

  private:
    vector<int> parent;
};

// Test main; all finds on same output line should be identical
int main( )
{
    int numElements = 128;
    int numInSameSet = 16;

    DisjSets ds{ numElements };
    int set1, set2;

    for( int k = 1; k < numInSameSet; k *= 2 )
    {
        for( int j = 0; j + k < numElements; j += 2 * k )
        {
            set1 = ds.find( j );
            set2 = ds.find( j + k );
            ds.unionSets( set1, set2 );
        }
    }

    for( int i = 0; i < numElements; ++i )
    {
        cout << ds.find( i ) << "*";
        if( i % numInSameSet == numInSameSet - 1 )
            cout << endl;
    }
    cout << endl;

    return 0;
}
