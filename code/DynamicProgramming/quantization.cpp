#include <iostream>
#include <vector>
#include <cstring> // memset()
#include <algorithm>
using namespace std;

const int INF = 987654321;

// A[]: ��Ҫ���������� ���ź��� 
// pSum[]: ���� A[] �Ĳ��ֺ� pSum[i]����A[0] ... A[i] ���ܺ� 
// pSqSum[]: ���� A[]ƽ�� �Ĳ��ֺ� pSqSum[i]����A[0]^2 ... A[i]^2 ���ܺ� 

vector<int> A {1, 744, 755, 4, 897, 902, 890, 6, 777};
int n = A.size();
vector<int> pSum(101), pSqSum(101);

void precalc() {
	sort(A.begin(), A.end());
	pSum[0] = A[0];
	pSqSum[0] = A[0] * A[0];
	for(int i=1; i<n; ++i) {
		pSum[i] = pSum[i-1] + A[i];
		pSqSum[i] = pSqSum[i-1] + A[i] * A[i];
	}
}

int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo==0 ? 0 : pSum[lo-1]);
	int sqSum = pSqSum[hi] - (lo==0 ? 0 : pSqSum[lo-1]);
	int mean = int( 0.5 + (double)sum/(hi-lo+1) );
	int ret = sqSum - 2*mean*sum + mean*mean*(hi-lo+1);
	return ret;
}

int cache[101][11];
int quantize(int from, int parts) {
	if(from == n) return 0;
	if(parts == 0) return INF;
	
	int& ret = cache[from][parts];
	if(ret != -1) return ret;
	
	ret = INF;
	for(int partSize=1; from+partSize<=n; ++partSize)
	    ret = min(ret,
			minError(from, from+partSize-1) + quantize(from+partSize, parts-1) );
	return ret;
}

int main() {
	memset(cache, -1, sizeof(cache));
	precalc();
// 	for (auto a : pSqSum) {
//        std::cout << a << " ";
//    }
    
	cout << quantize(0, 3) << endl;
	
	return 0;
}
