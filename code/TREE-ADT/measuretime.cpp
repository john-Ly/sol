#include <iostream>
#include <vector>
#include <algoritm>
#include <limits>
using namespace std;

// ʵ����״����
// �ܹ���������������� A[]�Ĳ��ֺ�
// ��ʼ��ʱ �� A[] ��ȫ��Ԫ����Ϊ 0
struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n+1) { }
	
	// �� A[0...pos]�Ĳ��ֺ�
	int sum(int pos) {
		// �����±�� 1 ��ʼ
		++pos;
		int ret = 0;
		while(pos > 0) {
			ret += tree[pos];
			// Ϊ���ҳ���������������Ҳ�� 1 ��Ϊ 0
			pos &= (pos-1);
		}
		return ret;
	}
	
	// �� A[pos]���� val
	void add(int pos, int val) {
		++pos;
		while(pos < tree.size() ){
			tree[pos] += val;
			pos += (pos & -pos);
		}
	} 
}; 
