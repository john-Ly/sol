#include <iostream>
#include "DisjSets.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int numElements = 16384;
    int numInSameSet = 128;

    DisjSets ds( numElements );
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
