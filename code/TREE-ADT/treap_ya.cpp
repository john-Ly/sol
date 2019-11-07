#include <cstdlib> // rand 
/*
std::srand(std::time(0)); // use current time as seed for random generator
int random_variable = std::rand();
*/
#include <utility>
#include <iostream>
using namespace std;

// 线性同余随机数生成器 
// A[0] = 1983
// A[i] = (A[i-1]*a+b) mod 20090711
struct RNG {
    int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) { }
	
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

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

// 返回小于 key 的键值个数 
int countLessThan(Node* root, KeyType key) {
	if(root == nullptr) return 0;
	if(root->key >= key)
 		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	
	return ls + 1 + countLessThan(root->right, key);
}
// 给出特定范围 [a, b) 求出此范围内的所有元素的个数
// countLessThan(b) - countLessThan(a) 


int runningMedian(int n, RNG rng) {
	Node* root = nullptr;
	int ret = 0;
	for(int cnt=1; cnt<=n; ++cnt) {
		root = insert(root, new Node(rng.next()));
		int median = kth(root, (cnt+1) / 2)->key;
		ret = (ret + median) % 20090711;
	}
	return ret;
}

int main()
{	
	RNG rng(1, 1);
	int ret = runningMedian(10, rng);
	cout << ret << endl;

    return 0;
}
