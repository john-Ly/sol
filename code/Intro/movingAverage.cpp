#include <iostream>
#include <vector>
using namespace std;

vector<double> movingAverage1(const vector<double>& A, int M) {
	vector<double> ret;
	int N = A.size();
	for(int i=M-1; i<N; ++i) {
		double partialSum = 0;
		/*
			for (int k=i; i-k<M; k--)
			sum += a[k];
			----------------
			It works, but it is not straight.
		*/
		for(int j=0; j<M; ++j)
		    partialSum += A[i-j];
		ret.push_back( partialSum/M );
	}
	return ret;
}

// Simple moving average
vector<double> movingAverage2(const vector<double>& A, int M) {
	vector<double> ret;
	int N = A.size();
	double partialSum = 0;
	
	for(int i=0; i<M-1; ++i)
		partialSum += A[i];
	for(int i=M-1; i<N; ++i) {
		partialSum += A[i];
	    ret.push_back( partialSum/M );
		partialSum += A[i-(M+1)];
	}
	return ret;
}

int main() {
	vector<double> a {1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2, 12.2};
    vector<double> tmp;
    tmp = movingAverage1(a, 3);
    for(const auto i : tmp) cout << i << " | ";
    cout << "\n";
    
    tmp.clear();
    tmp = movingAverage2(a, 3);
    for(const auto i : tmp) cout << i << " | ";
    cout << "\n";
    
    return 0;
}
