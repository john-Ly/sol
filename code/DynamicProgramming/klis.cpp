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
// 返回 a[start] 起始 lis 的长度
int lis(int start) {
	int& ret = cacheLen[start+1];
	if(ret != -1) return ret;
	
	ret = 1;
	for(int next=start+1; next<a.size(); ++next)
	    if(start == -1 || a[start]<a[next])
 		    ret = std::max(ret, 1+lis(next));
	return ret;
}

// 返回 a[start] 起始 lis 的个数
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

// 计算第 k 个 LIS
// 把第一个序列保存到 lis
void reconstruct(int start, int skip, vector<int>& _lis) {
	// 1. a[start] 总是在 lis 中 
	if(start != -1) _lis.push_back(a[start]);
	
	// 2. 生成可摆放到后面的数字和位置的目录
	// 形成(数字 数字的位置) 形式的目录
	vector<pair<int, int> > followers;
	for(int next=start+1; next<a.size(); ++next)
	    if( (start == -1 || a[start]<a[next]) &&
	    	    lis(start) == lis(next) + 1 )
	    	followers.push_back(std::make_pair(a[next], next));
//	for(auto i : followers) cout << i.first << " " << i.second << "+++";
//	cout << endl;	
	sort(followers.begin(), followers.end());
	// 按照 i <pair>.first 升序排列 
	
	// 2. 求出第 k 个 LIS 的下一个数字 
	for(int i=0; i<followers.size(); ++i) {
		// 求出能够包含当前数字的 LIS 的个数
		int idx = followers[i].second;
		int cnt = count(idx);
		if(cnt <= skip) skip -= cnt;
		else {
			// 得知下一个数字是 S[idx]
			// 4. 利用递归调用
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
