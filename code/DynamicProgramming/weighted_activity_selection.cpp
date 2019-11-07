// C++ program for weighted job scheduling using Naive Recursive Method
#include <iostream>
#include <algorithm>
#include <cstring> // memset()
using namespace std;
 
struct Job {
    int start, finish, profit;
};

int latestNonConflict(Job arr[], int i) {
    for (int j=i-1; j>=0; j--) {                 // which can be optimized
        if (arr[j].finish <= arr[i-1].start)
            return j;
    }
    return -1;
}

int findMaxProfitRec(Job arr[], int n)
{
    // Base case
    if (n == 1) return arr[0].profit;
 
    // Find profit when current job is inclueded
    int inclProf = arr[n-1].profit;
    int i = latestNonConflict(arr, n);
    if (i != -1)
      inclProf += findMaxProfitRec(arr, i+1);
 
    int exclProf = findMaxProfitRec(arr, n-1);
 
    return max(inclProf,  exclProf);
}

// stores the profit for jobs till arr[i] (including arr[i])
int cache[5];
int findMaxProfitDp(Job arr[], int n) {
	int& ret = cache[n];
	if (n == 1) return ret = arr[0].profit;
	
	if(ret != -1) return ret;
 
 	ret = findMaxProfitDp(arr, n-1);
 	int i = latestNonConflict(arr, n);
 	if (i != -1)
        ret = max(ret, findMaxProfitDp(arr, i+1) + arr[n-1].profit);
 
    return ret;
}

int main() {
    Job arr[] = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
    int n = sizeof(arr)/sizeof(arr[0]);
    sort(arr, arr+n, [](Job a, Job b){return a.finish < b.finish;} );
    memset(cache, -1, sizeof(cache));
    cout << "The optimal profit is " << findMaxProfitDp(arr, n);
    return 0;
}
