#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// fixed-head solution
void permutation(vector<int>& v, int start) {
	int n = v.size();
	if( (start+1) == n) {
		for(auto i : v) cout << i;
		cout << endl;
	}
	else {
		for(int i=start; i<n; ++i) {
		    // if(v[start] == v[i+1]) continue;
			// else {
		    	swap(v[i], v[start]);
			    permutation(v, start+1);
			    swap(v[i], v[start]);
			//}
		}
	}
}

/* 用不了递归 如果利用 BFS 需要额外的存储空间
void overturn(vector<int>& v) {
	int n = v.size();
	if( (start+1) == n) {
		for(auto i : v) cout << i;
		cout << endl;
	}

	for(int i=0; i<n; ++i) {
	    for(int j=i+1; j=<n; ++j) {
		    reverse(here.begin()+i, here.begin()+j);

			// for each pass, start the original order
	    	reverse(here.begin()+i, here.begin()+j);
		}
	}
}
*/

int main() {
	vector<int> a {0, 1, 2};
	// permutation(a, 0);
	// permutation(a, 1);
	// permutation(a, 2);
	permutation(a, 3);

	return 0;
}
