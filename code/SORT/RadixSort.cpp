#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "UniformRandom.h"
using namespace std;

// Radix sort use bucket each pass. The number of passes = base

/*
 * Radix sort an array of Strings
 * Assume all are all ASCII
 * Assume all have same length
 *
 * The trick is to use several passes of bucket sort.
 * Cause uniformly distributed, so can apply to each string within each buckets of bucket. 
 */
void radixSortA( vector<string> & arr, int stringLen )
{
    const int BUCKETS = 256;

    vector<vector<string>> buckets( BUCKETS );

    for( int pos = stringLen - 1; pos >= 0; --pos )
    {
        for( string & s : arr )
            buckets[ s[ pos ] ].push_back( std::move( s ) );

        int idx = 0;
        for( auto & thisBucket : buckets )
        {
        	// if (thisBucket.size())  -- may be fast
            for( string & s : thisBucket )
                arr[ idx++ ] = std::move( s );

            thisBucket.clear( );
        }
    }
}

/*
 * Counting radix sort an array of Strings
 * Assume all are all ASCII
 * Assume all have same length
 */
void countingRadixSort( vector<string> & arr, int stringLen )
{
    const int BUCKETS = 256;

    int N = arr.size( );
    vector<string> buffer( N );

    vector<string> *in = &arr;
    vector<string> *out = &buffer;

    for( int pos = stringLen - 1; pos >= 0; --pos )
    {
        vector<int> count( BUCKETS + 1 );

        for( int i = 0; i < N; ++i )
            ++count[ (*in)[ i ][ pos ] + 1 ];

        for( int b = 1; b <= BUCKETS; ++b )
            count[ b ] += count[ b - 1 ];

        for( int i = 0; i < N; ++i )
            (*out)[ count[ (*in)[ i ][ pos ] ]++ ] = std::move( (*in)[ i ] );
        // satble sort

        // swap in and out roles
        std::swap( in, out );
    }

    // if odd number of passes, in is buffer, out is arr; so copy back
    if( stringLen % 2 == 1 )
        for( int i = 0; i < arr.size( ); ++i )
            (*out)[ i ] = std::move( (*in)[ i ] );
}

/*
 * Radix sort an array of Strings
 * Assume all are all ASCII
 * Assume all have length bounded by maxLen
 */
void radixSort( vector<string> & arr, int maxLen )
{
    const int BUCKETS = 256;

    vector<vector<string>> wordsByLength( maxLen + 1 );
    vector<vector<string>> buckets( BUCKETS );

    for( string & s : arr )
        wordsByLength[ s.length( ) ].push_back( std::move( s ) );

    int idx = 0;
    for( auto & wordList : wordsByLength )
        for( string & s : wordList )
            arr[ idx++ ] = std::move( s );

    int startingIndex = arr.size( );    
    for( int pos = maxLen - 1; pos >= 0; --pos )
    {
        startingIndex -= wordsByLength[ pos + 1 ].size( );

        for( int i = startingIndex; i < arr.size( ); ++i )
            buckets[ arr[ i ][ pos ] ].push_back( std::move( arr[ i ] ) );

        idx = startingIndex;
        for( auto & thisBucket : buckets )
        {
            for( string & s : thisBucket )
                arr[ idx++ ] = std::move( s );

            thisBucket.clear( );
        }
    }
}

int main( )
{
    vector<string> lst;
    UniformRandom r;

    const int LEN = 5;
    const int ADD = 7;

    for( int i = 0; i < 1000000; ++i )
    {
        string str = "";
        int len = LEN + ADD; //r.nextInt( ADD ); // between 5 and 11 characters

        for( int j = 0; j < len; ++j )
            str += static_cast<char>( 'a' + r.nextInt( 26 ) );

        lst.push_back( str );
    }

    vector<string> arr1 = lst;
    vector<string> arr2 = lst;
    
    // cout << arr1.size( ) << endl;   1 000 000 items of string in vector.

    sort( begin( arr1 ), end( arr1 ) );
    radixSortA( arr2, LEN + ADD );

    for( int i = 0; i < arr1.size( ); ++i )
        if( arr1[ i ] != arr2[ i ] )
            cout << "OOPS!!" << endl;
    
    return 0;
}
