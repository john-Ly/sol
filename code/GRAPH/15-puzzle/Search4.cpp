#include <iostream>
#include "N_puzzle.h"
#include "Updatable_heap.h"

using namespace std;
using namespace Data_structures;

template <int N>
void go( N_puzzle<N> const &, int = 1 );

int main() {
	srand( 539 );
	N_puzzle<4> pz4;

	for ( int i = 0; i < 10000; ++i ) {
		pz4 = N_puzzle<4>();

		while( !pz4.solvable() ) {
			pz4 = N_puzzle<4>();
		}

		cout << "-----------------------------------------------------------" << endl;
		cout << pz4 << endl;
		go( pz4, 1000000000 );
	}

	return 0;
}

int const M = 32*1024*1024;

template <int N>
void go( N_puzzle<N> const &pz, int max_n ) {
	if ( !pz.solvable() ) {
		return;
	}

	Data_structures::Updatable_heap<N_puzzle<N>, M> heap;
	heap.push( pz, 0 );

	int n = 0;

	while( heap.size() != 0 && n != max_n ) {
		N_puzzle<N> top = heap.pop();
		++n;

		if ( top == N_puzzle<N>::solution() ) {
			// We are done
			std::cout << "Path length:         " << heap.length( top )  << std::endl;
			std::cout << "Maximum heap size:   " << heap.maximum_size() << std::endl;
			std::cout << "Vertices searched:   " << n                   << std::endl;

			return;
		}

		if ( top.tile_left_possible() ) {
			heap.push( top.tile_left(), heap.length( top ) + 1 );
		}

		if ( top.tile_right_possible() ) {
			heap.push( top.tile_right(), heap.length( top ) + 1 );
		}

		if ( top.tile_up_possible() ) {
			heap.push( top.tile_up(), heap.length( top ) + 1 );
		}

		if ( top.tile_down_possible() ) {
			heap.push( top.tile_down(), heap.length( top ) + 1 );
		}
	}
}
