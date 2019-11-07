#include <iostream>
#include "N_puzzle.h"

using namespace std;

int main() {
	N_puzzle<3> pz;

	cout << pz;
	cout << "Distance: " << pz.length() << endl << endl;
	cout << pz.tile_up();
	cout << "Distance: " << pz.tile_up().length() << endl << endl;
	cout << pz.tile_down();
	cout << "Distance: " << pz.tile_down().length() << endl << endl;
	cout << pz.tile_left();
	cout << "Distance: " << pz.tile_left().length() << endl << endl;
	cout << pz.tile_right();
	cout << "Distance: " << pz.tile_right().length() << endl << endl;

	cout << N_puzzle<3>::solution() << endl;
	cout << N_puzzle<3>::solution().solvable() << endl;
}
