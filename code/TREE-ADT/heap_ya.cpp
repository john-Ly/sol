#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 用可以动态扩容的vector实现完全二叉树
// 二进制堆： 两个形状规则
//  (1.除最后一层外 其余所有层必须填满节点)
//  (2.最后一层外 必须从最侧开始填充节点)
// 大小关系规则(父节点拥有的元素要大于子节点)

// @TODO
// 1. 如何计算堆高度
// 2. 生成堆 的时间复杂度 O(n) , 但是建堆的目的是取出最值 总的时间复杂度为O(n lg n)
// 使用每次读入一个项, 然后push_heap的方式 也是O(n lg n)
vector<int> heap;

// 先满足形状关系, 在满足大小关系
// time: O(lg n)
void push_heap(vector<int>& heap, int newValue) {
	// 向堆的末端插入 newValue
	heap.push_back(newValue);
	// newValue 当前位置
	int idx = heap.size() - 1;
	// 直至到达根节点或遇到包含比 newValue 更大元素的父节点为止
    // 每次循环进入树的上一层
	while(idx>0 && heap[(idx-1)/2] < heap[idx]){
		swap(heap[idx], heap[(idx-1)/2]);
		idx = (idx-1) / 2;
	}
}

// 从拥有整数元素的最大堆中删除最大元素
// time: O(lg n)
void pop_heap(vector<int>& heap) {
	// 从堆的末端得到元素值并覆盖根节点
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;
    // 每次循环会移动到树的下一层
	while(true) {
		int left = here * 2 + 1, right = here * 2 + 2;
		// 到达叶节点时
		if(left >= heap.size()) break;
		int next = here;
		if(heap[next] < heap[left])
			next = left;
		if(right < heap.size() && heap[next] < heap[right])
	 		next = right;
		if(next == here) break;
		swap(heap[here], heap[next]);
		here = next;
	}
}

// heap_sort 删除最大值之后 最后一个元素的位置是空的 因此heap_sort可以原地排序(排序不是稳定的)
void heap_sort(vector<int>& v) {
	for(auto i : v) push_heap(heap, i);

	for(int i=v.size()-1; i>=0; --i) {
		v[i] = heap.front();
		pop_heap(heap);
	}
}

int main() {
	vector<int> v{5, 1, 4, 3, 2};
	heap_sort(v);
	for(auto i : v)
      	cout << i << " ";
    cout << endl;

	return 0;
}
