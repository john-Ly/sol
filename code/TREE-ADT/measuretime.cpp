#include <iostream>
#include <vector>
#include <algoritm>
#include <limits>
using namespace std;

// 实现树状数组
// 能够快速求出虚拟数组 A[]的部分和
// 初始化时 将 A[] 的全部元素视为 0
struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n+1) { }
	
	// 求 A[0...pos]的部分和
	int sum(int pos) {
		// 设想下标从 1 起始
		++pos;
		int ret = 0;
		while(pos > 0) {
			ret += tree[pos];
			// 为了找出下以区间而把最右侧的 1 改为 0
			pos &= (pos-1);
		}
		return ret;
	}
	
	// 给 A[pos]加上 val
	void add(int pos, int val) {
		++pos;
		while(pos < tree.size() ){
			tree[pos] += val;
			pos += (pos & -pos);
		}
	} 
}; 
