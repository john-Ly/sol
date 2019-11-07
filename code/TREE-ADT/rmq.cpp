#include <iostream>
#include <vector>
#include <algoritm>
#include <limits>
using namespace std;

const int INT_MAX = numeric_limits<int>::max();

// RMQ - range minimum query ������Сֵ��ѯ���� 
// ������� RMQ �������������ʵ�ַ��� 
struct RMQ {
    int n; // ���鳤��
	vector<int> rangeMin; // ��������Сֵ
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n-1, 1);	
	}
	
	// node�ڵ��ʾ array[left, right]ʱ
	// ��ʼ�� nodeΪ���ڵ������ �����ش��������Сֵ
	int init(const vector<int>& array, int left, int right, int node) {
		if(left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node*2);
		int rightMin = init(array, mid+1, right, node*2+1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	
	// ���� node ��ʾ������array[nodeLeft...nodeRight]ʱ,
	// ���������� array[left...right]����Ľ�������Сֵ
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// �������䲻�ص��򷵻ؼ���ֵ: ����
		if(right < nodeLeft || nodeRight < left) return INT_MAX;
		// node ��ʾ�ķ�Χ��ȫ������ array[left...right]
		if(left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		// �ָ��������������ϲ����
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node*2, nodeLeft, mid),
			   query(left, right, node*2+1, mid, nodeRight) );
	}
	// �ӿ� 
	int query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}
	
	// array[index] = ����Ϊ newValue 
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		// index ��ڵ��ʾ�������޹�--����
		if(index < nodeLeft || nodeRight < index)
	 		return rangeMin[node];
		// �Ѿ��Ƶ�����Ҷ�ڵ�
		if(nodeLeft == nodeRight)
			return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(
			   update(index, newValue, node*2, nodeLeft, mid),
			   update(index, newValue, node*2+1, mid, nodeRight)
			   ); 
	}
	
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n-1);
	}
};

int main()
{	

    return 0;
}
