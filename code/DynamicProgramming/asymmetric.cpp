#include <iostream>
#include <vector>
#include <cstring> // memset()
using namespace std;

const int MOD = 1000000007;

int cache[101];
int tiling(int width) {
	if(width <= 1) return 1;
	
	int& ret = cache[width];
	if(ret != -1) return ret;

	return ret = ( tiling(width-2)+tiling(width-1) ) % MOD;
}

int asymmetric(int width) {
	if(width%2 == 1)
        return ( tiling(width) - tiling(width/2) + MOD ) % MOD;
    int ret = tiling(width);
    ret = (ret - tiling(width/2) + MOD) % MOD;
    ret = (ret - tiling(width/2-1) + MOD) % MOD;
	return ret;
}

int main() {
	memset(cache, -1, sizeof(cache));
	
	cout << tiling(4) << endl;
	cout << asymmetric(4) << endl;
	
	return 0;
}
