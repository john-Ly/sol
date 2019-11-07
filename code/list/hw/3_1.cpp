#include<iostream>
using namespace std;

void printLots(const list<int>& printLst, const list<int>& pos)               //runtime O(n2)
{
 list<int>::const_iterator pit;
 for(list<int>::const_iterator it = pos.begin(); it != pos.end(); ++it)
 {
  pit = printLst.begin();
  for(int i = 0; i < *it; ++i)
  {
   ++pit;
  }
  cout << *pit << " ";
 }
}

void printLots2(const list<int>& printLst, const list<int>& pos)               //runtime O(n)??
{
 list<int>::const_iterator it, pit;
 int cnt;
 for( it = pos.begin(), pit = printLst.begin(), cnt = 0; it != pos.end(); ++it)
 {
  while(cnt != *it)
  {
   ++pit;
   ++cnt;
  }
  cout << *pit << " ";
 }
}

int main() {
	int a[] = {0,3,4,6};
	int b[] = {0,1,2,3,4,5,6,7};
	list<int> L(a, a+4);
	list<int> P(b,b+8);
	
	printLots2(P,L);
	
	return 0;
}
