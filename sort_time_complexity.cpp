// case for analyse time complexity

#include <vector>
using namespace std;

void selectionSort(vector<int>& A) {
	int n = A.size();
	for(int i=0; i<n; ++i) {
		int minIndex = i;
		for(int j=i+1; j<n; ++j) {
			if(A[minIndex]>A[j])
			    minIndex = j; 
			std::swap(A[i], A[minIndex]);
		}
	} 
}

void insertionSort(vector<int>& A) {
	int n = A.size();
	for(int i=0; i<n; ++i) {
		int j = i;
		while(j>0 && A[j-1]>A[j]){
			std::swap(A[j-1], A[j]);
			--j;
		}
	} 
}

int binsearch(const vector<int>& A, int x) {
	int n = A.size();
	int lo = -1, hi = n;
	while(lo+1 < hi) {
		int mid = (lo+hi) / 2;
		if(A[mid] < x)
		    lo = mid;
		else
			hi = mid;
	}
	return hi;
}
