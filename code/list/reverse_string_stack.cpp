#include<iostream>
#include<stack>

void reverseString(char *C, int n){
	stack<char> S;

	// loop for push
	for(int i=0; i<n; i++){
		S.push(C[i]);
	}

	// loop for pop
	for(int i=0; i<n; i++){
		C[i] = S.top();
		S.pop();
	}
}

/*
time complexity: O(n)
space complexity: O(n)

actually, better solution: use i,j to mark the begin and end,
  while(i<=j){
	  swap(C[i], C[j]);
	  i++;
	  j--;
  }
don't need extral memory, time O(n/2) = O(n)
*/