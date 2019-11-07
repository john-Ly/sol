#include <iostream>
#include <vector>
#include <algorithm>  // max, sort
#include <utility>  // pair
#include <cstring> // memset()
using namespace std;

vector<int> a { 5, 1, 6, 4, 3, 2, 8, 7 };
// vector<int> a { 5, 6, 1, 2 };
// vector<int> a { 5 };

const int MAX = 2000000000 + 1;

int cacheLen[11], cacheCnt[11];
// ���� a[start] ��ʼ lis �ĳ���
int lis(int start) {
	int& ret = cacheLen[start+1];
	if(ret != -1) return ret;
	
	ret = 1;
	for(int next=start+1; next<a.size(); ++next)
	    if(start == -1 || a[start]<a[next])
 		    ret = std::max(ret, 1+lis(next));
	return ret;
}

// ���� a[start] ��ʼ lis �ĸ���
int count(int start) {
	int& ret = cacheCnt[start+1];
	if(lis(start) == 1) return ret = 1;
	
	if(ret != -1) return ret;
	
	ret = 0;
	for(int next=start+1; next<a.size(); ++next)
	    if( (start == -1 || a[start]<a[next]) &&
	    	  lis(start) == lis(next) + 1 )
 		    ret = std::min<long long>(MAX, (long long)ret+count(next) );
	return ret;
}

// ����� k �� LIS
// �ѵ�һ�����б��浽 lis
void reconstruct(int start, int skip, vector<int>& _lis) {
	// 1. a[start] ������ lis �� 
	if(start != -1) _lis.push_back(a[start]);
	
	// 2. ���ɿɰڷŵ���������ֺ�λ�õ�Ŀ¼
	// �γ�(���� ���ֵ�λ��) ��ʽ��Ŀ¼
	vector<pair<int, int> > followers;
	for(int next=start+1; next<a.size(); ++next)
	    if( (start == -1 || a[start]<a[next]) &&
	    	    lis(start) == lis(next) + 1 )
	    	followers.push_back(std::make_pair(a[next], next));
//	for(auto i : followers) cout << i.first << " " << i.second << "+++";
//	cout << endl;	
	sort(followers.begin(), followers.end());
	// ���� i <pair>.first �������� 
	
	// 2. ����� k �� LIS ����һ������ 
	for(int i=0; i<followers.size(); ++i) {
		// ����ܹ�������ǰ���ֵ� LIS �ĸ���
		int idx = followers[i].second;
		int cnt = count(idx);
		if(cnt <= skip) skip -= cnt;
		else {
			// ��֪��һ�������� S[idx]
			// 4. ���õݹ����
			reconstruct(idx, skip, _lis);
			break;
		} 
	}
}

int main( ) {
	memset(cacheLen, -1, sizeof(cacheLen));
	memset(cacheCnt, -1, sizeof(cacheCnt));
    cout << "longest length is " << lis(-1) - 1 << endl;
    cout << "num of longest " << count(-1) << endl;
	
	vector<int> tmp;
	int start = -1, skip = 6-1;
	reconstruct(start, skip, tmp);
	for(auto i : tmp) cout << i << " ";
	cout << endl;

/*
	for(int i=0; i<9; ++i)
	    cout << cacheLen[i] << "  ";
	cout << endl;
	for(int i=0; i<9; ++i)
	    cout << cacheCnt[i] << " ";
*/	    

    return 0;
}
