#include <iostream>
#include "N_puzzle.h"
#include "Updatable_heap.h"

using namespace std;
using namespace Data_structures;

template <int N>
void go( N_puzzle<N> const & );

int main() {
	N_puzzle<3> pz1 = N_puzzle<3>::solution();
	cout << "Solvable? " << pz1.solvable() << endl;
	go( pz1 );

	// int array[9] = {2,5,3,4,1,6,0,7,8};
	// int array[9] = {1, 2, 3, 4, 5, 6, 8, 7, 0};
	cout << "-----------------------------------------------------------" << endl;
	int array[9] = {0, 3, 2, 8, 7, 1, 4, 5, 6};
	N_puzzle<3> pz2( array );
	cout << "Solvable? " << pz2.solvable() << endl;
	cout << pz2 << endl;
	go( pz2 );
	cout << "-----------------------------------------------------------" << endl;

	N_puzzle<3> pz3;

	while( !pz3.solvable() ) {
		pz3 = N_puzzle<3>();
	}

	cout << "Solvable? " << pz3.solvable() << endl;
	cout << pz3 << endl;
	go( pz3 );

	N_puzzle<3> pz4;

	for ( int i = 0; i < 100; ++i ) {
		pz4 = N_puzzle<3>();

		while( !pz4.solvable() ) {
			pz4 = N_puzzle<3>();
		}

		cout << "-----------------------------------------------------------" << endl;
		cout << pz4 << endl;
		go( pz4 );
	}

	return 0;
}

int const M = 1024*1024;

template <int N>
void go( N_puzzle<N> const &pz ) {
	if ( !pz.solvable() ) {
		return;
	}

	Data_structures::Updatable_heap<N_puzzle<N>, M> heap;
	heap.push( pz, 0 );

	int n = 0;

	while( heap.size() != 0 ) {
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
