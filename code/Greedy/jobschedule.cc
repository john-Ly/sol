#include<iostream>
#include<algorithm>
#include<limits>
#include<vector>
using namespace std;

// https://www.geeksforgeeks.org/job-sequencing-problem/
// Program to find the maximum profit job sequence from a given array
// of jobs with deadlines and profits
// 每个job的执行时间相同
struct Job {
   char id;
   int dead, profit;  // Profit if job is over before or on deadline
};

class DisjSets {
  public:
    explicit DisjSets( int n ) : parent(n+1) {
    	for (int i=0; i<=n; ++i)
    		parent[i] = i;
	}

	// path compression + return root
    int find( int u ) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	// O(lg N)
    void unionSets( int u, int v ) {
		u = find(u); v = find(v);
		if (u == v) return;
		parent[u] = v;
	}

  private:
    vector<int> parent;
};

// also using <multiset> which provide loewe_bounder
// time-comsumption   space-comsumption
int findMaxDeadline(struct Job arr[], int n) {
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, arr[i].dead);
    return ans;
}

// Returns minimum number of platforms reqquired
void printJobScheduling(Job arr[], int n) {
    // Sort all jobs according to decreasing order of prfit
    sort( arr, arr+n, [](Job& a, Job& b){return a.profit > b.profit;} );

    int result[n]; // To store result (Sequence of jobs)
    bool slot[n];  // To keep track of free time slots

    // Initialize all slots to be free
    for (int i=0; i<n; i++)
        slot[i] = false;

    // Iterate through all given jobs
    for (int i=0; i<n; i++) {
       // Find a free slot for this job (Note that we start
       // from the last possible slot)
       for (int j=min(n, arr[i].dead)-1; j>=0; j--) {
          // Free slot found
            if (slot[j]==false) {
               result[j] = i;  // Add this job to result
               slot[j] = true; // Make this slot occupied
               break;
            }
        }
    }

    // Print the result
    for (int i=0; i<n; i++)
        if (slot[i])
           cout << arr[result[i]].id << " ";
}

// Returns minimum number of platforms reqquired
void jobS2(Job arr[], int n) {
    // Sort all jobs according to decreasing order of prfit
    sort( arr, arr+n, [](Job a, Job b){return a.profit > b.profit;} );

    int maxDeadline = findMaxDeadline(arr, n);
    DisjSets ds(maxDeadline);

    for (int i=0; i<n; i++) {
        // Find the maximum available free slot for
        // this job (corresponding to its deadline)
        int availableSlot = ds.find(arr[i].dead);

        if (availableSlot > 0) {
			// parent is the latter parameter
            ds.unionSets(ds.find(availableSlot), availableSlot-1);
            cout << arr[i].id << " ";
        }
    }
}

/*
Input:  Five Jobs with following deadlines and profits
   JobID     Deadline     Profit
     a         2           100
     b         1           19
     c         2           27
     d         1           25
     e         3           15
Output: Following is maximum profit sequence of jobs
        c, a, e
*/

int main() {
    Job arr[] = { {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27},
                {'d', 1, 25}, {'e', 3, 15}};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Following is maximum profit sequence of jobs\n";
    printJobScheduling(arr, n);
    // jobS2(arr, n);
    return 0;
}
