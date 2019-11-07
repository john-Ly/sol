#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib> // rand 
/*
std::srand(std::time(0)); // use current time as seed for random generator
int random_variable = std::rand();
*/
#include <iostream>
using namespace std;

void insertSort(vector<int>& A) {
	for(int i=0; i<A.size(); ++i) {
		// 向 A[0..i-1] 插入 A[i]
		int j = i;
		while(j>0 && A[j-1] > A[j]) {
			// 不变式 a: A[j+1..i]区间内所有元素都大于 A[j]
			// 不变式 b: A[0..i]区间内除 A[j]外的所有元素已经排好序
			swap(A[j-1], A[j]);
			--j;
		}
	}
}

typedef int KeyType;
// 保存树堆节点
struct Node {
	KeyType key;
	// 将当前节点用作根节点的子树的大小 
	int priority, size;
	Node *left, *right;
	// 生成器生成随机数后, 初始化size和 left/right
	Node(const KeyType& _key) : key(_key), priority(rand()),
 			   size(1), left(nullptr), right(nullptr) { }
	
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	// 更新size成员
	void calcSize() {
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;
// 将以 root 为根的树堆分割成所有元素值小于 key的树堆 以及大于 key的树堆
NodePair split(Node* root, KeyType key) {
	if(root == nullptr) return NodePair(nullptr, nullptr);
	
	// 如果根节点中的元素小于 key, 分割右子树
	if(root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// 如果根节点中的元素大于 key, 分割左子树
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
} // 利用递归的思想理解 

Node* insert(Node* root, Node* node) {
	if(root == nullptr) return node;
	// 需要用 node 替换根节点。将该子树一分为二 
	// 分别充当左右侧后代节点
	if(root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	} else if (node->key < root->key)
	  	root->setLeft( insert(root->left, node) );
	else
		root->setRight( insert(root->right, node) );
}
// root = insert(root, new Node(value));

Node* merge(Node* a, Node* b) {
	if(a==nullptr) return b;
	if(b==nullptr) return a;
	if(a->priority < b->priority) {
		b->setLeft(merge(a, b->left));	// 如果不是 treap 合并顺序... 
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

// 以 root 为根的树堆中, 删除 key 后返回树堆的根
// 时间复杂度正比于 树高 O(lg N)
Node* erase(Node* root, KeyType key) {
	if(root == nullptr) return root;
	// 删除 root 后合并两个子树并返回
	if(root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if(key < root->key)
		root->setLeft( erase(root->left, key) );
	else
		root->setRight( erase(root->right, key) );
	return root;
}

// 查找树中 第 k 个元素的算法
// 时间复杂度正比于 树高 O(lg N)
Node* kth(Node* root, int k) {
	int leftSize = 0;
	if(root->left != nullptr) leftSize = root->left->size;
	if(k <= leftSize) return kth(root->left, k);
	if(k == leftSize + 1) return root;
	return kth(root->right, k-leftSize-1);
}

// 反转插入排序 
vector<int> solve(vector<int>& shifted) {
	int n = shifted.size();
	vector<int> ret;
	Node* candidates = nullptr;
	for(int i=0; i<n; ++i)
		candidates = insert(candidates, new Node(i+1));
	// 从最后一个位置开始添加 A[]
	for(int i=n-1; i>=0; --i) {
		// 大于此数值的后续安置共有 larger个
		int larger = shifted[i];
		Node* k = kth(candidates, i+1-larger);
		ret[i] = k->key;
		candidates = erase(candidates, k->key);
	}
	return ret;
}

// 函数出现问题？？？ 
int main() {
	vector<int> shifted{0, 1, 1, 2, 3};
	for(auto i : solve(shifted) )
      	cout << i << " ";
      	
	return 0;
}
