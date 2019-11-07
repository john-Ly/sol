#include <iostream>
#include <limits>
#include <vector>
#include <cstring> // memset()
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) ((a) > (b) ? (a) > (c) ? (a) : (c) : (b) > (c) ? (b) : (c) )
// unsinght_32
const long long NEGINF = numeric_limits<long long>::min();

vector<int> a { 10, 20, 30, 1, 2 };
vector<int> b { 10, 20, 30 };
int cache[10][10];

// jlis[i, j] = 表示字符串A[i...]和B[j...]里面的jlis
int jlis(int idxA, int idxB) {
	int& ret = cache[idxA+1][idxB+1];
	if(ret != -1) return ret;
	ret = 2;
	long long m = (idxA == -1 ? NEGINF : a[idxA]);
	long long n = (idxB == -1 ? NEGINF : b[idxB]);
	long long maxElement = MAX(m, n);

	for(int nextA=idxA+1; nextA<a.size(); ++nextA) {
	    if(maxElement < a[nextA])
		    ret = MAX(ret, 1+jlis(nextA, idxB));
	}

	for(int nextB=idxB+1; nextB<b.size(); ++nextB) {
	    if(maxElement < b[nextB])
		    ret = MAX(ret, 1+jlis(idxA, nextB));
	}

	return ret;
}

int main( ) {
	memset(cache, -1, sizeof(cache));
    int cnt;

    cnt = jlis(-1, -1);
    cout << "join longest is " << cnt-2 << endl;

    for(int i=0; i<7; ++i) {
  		cout << endl;
        for(int j=0; j<7; ++j)
      		cout << cache[i][j] << '\t';
	}

    return 0;
}
