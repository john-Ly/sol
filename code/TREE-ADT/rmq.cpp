#include <iostream>
#include <vector>
#include <algoritm>
#include <limits>
using namespace std;

const int INT_MAX = numeric_limits<int>::max();

// RMQ - range minimum query 区间最小值查询问题 
// 解决数组 RMQ 问题的区间树的实现方法 
struct RMQ {
    int n; // 数组长度
	vector<int> rangeMin; // 各区间最小值
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n-1, 1);	
	}
	
	// node节点表示 array[left, right]时
	// 初始化 node为根节点的子树 并返回此区间的最小值
	int init(const vector<int>& array, int left, int right, int node) {
		if(left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node*2);
		int rightMin = init(array, mid+1, right, node*2+1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	
	// 给定 node 表示的区间array[nodeLeft...nodeRight]时,
	// 求出此区间和 array[left...right]区间的交集的最小值
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 两个区间不重叠则返回极大值: 忽略
		if(right < nodeLeft || nodeRight < left) return INT_MAX;
		// node 表示的范围完全包含于 array[left...right]
		if(left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		// 分割成两个区间计算后合并结果
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node*2, nodeLeft, mid),
			   query(left, right, node*2+1, mid, nodeRight) );
	}
	// 接口 
	int query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}
	
	// array[index] = 被换为 newValue 
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		// index 与节点表示的区间无关--忽略
		if(index < nodeLeft || nodeRight < index)
	 		return rangeMin[node];
		// 已经移到树的叶节点
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
