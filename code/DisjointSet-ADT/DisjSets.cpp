#include "DisjSets.h"

// Init
DisjSets::DisjSets( int numElements )
	: parent( numElements, -1 )
	{}

/**
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 */
void DisjSets::unionSets( int root1, int root2 ) {
    if( parent[ root2 ] < parent[ root1 ] )  // root2 is deeper
        parent[ root1 ] = root2;        // Make root2 new root
    else {
        if( parent[ root1 ] == parent[ root2 ] )
            --parent[ root1 ];          // Update height if same
        parent[ root2 ] = root1;        // Make root1 new root
    }
}

/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x ) const {
    if( parent[ x ] < 0 )
        return x;
    else
        return find( parent[ x ] );
}

// Perform a find with *path compression*.
int DisjSets::find( int x ) {
    if( parent[ x ] < 0 )
        return x;
    else
        return parent[ x ] = find( parent[ x ] );
}
