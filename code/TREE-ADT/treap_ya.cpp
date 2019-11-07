#include <cstdlib> // rand 
/*
std::srand(std::time(0)); // use current time as seed for random generator
int random_variable = std::rand();
*/
#include <utility>
#include <iostream>
using namespace std;

// ����ͬ������������� 
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
// �������ѽڵ�
struct Node {
	KeyType key;
	// ����ǰ�ڵ��������ڵ�������Ĵ�С 
	int priority, size;
	Node *left, *right;
	// �����������������, ��ʼ��size�� left/right
	Node(const KeyType& _key) : key(_key), priority(rand()),
 			   size(1), left(nullptr), right(nullptr) { }
	
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	// ����size��Ա
	void calcSize() {
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;
// ���� root Ϊ�������ѷָ������Ԫ��ֵС�� key������ �Լ����� key������
NodePair split(Node* root, KeyType key) {
	if(root == nullptr) return NodePair(nullptr, nullptr);
	
	// ������ڵ��е�Ԫ��С�� key, �ָ�������
	if(root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// ������ڵ��е�Ԫ�ش��� key, �ָ�������
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
} // ���õݹ��˼����� 

Node* insert(Node* root, Node* node) {
	if(root == nullptr) return node;
	// ��Ҫ�� node �滻���ڵ㡣��������һ��Ϊ�� 
	// �ֱ�䵱���Ҳ����ڵ�
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
		b->setLeft(merge(a, b->left));	// ������� treap �ϲ�˳��... 
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

// �� root Ϊ����������, ɾ�� key �󷵻����ѵĸ�
// ʱ�临�Ӷ������� ���� O(lg N)
Node* erase(Node* root, KeyType key) {
	if(root == nullptr) return root;
	// ɾ�� root ��ϲ���������������
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

// �������� �� k ��Ԫ�ص��㷨
// ʱ�临�Ӷ������� ���� O(lg N)
Node* kth(Node* root, int k) {
	int leftSize = 0;
	if(root->left != nullptr) leftSize = root->left->size;
	if(k <= leftSize) return kth(root->left, k);
	if(k == leftSize + 1) return root;
	return kth(root->right, k-leftSize-1);
}

// ����С�� key �ļ�ֵ���� 
int countLessThan(Node* root, KeyType key) {
	if(root == nullptr) return 0;
	if(root->key >= key)
 		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	
	return ls + 1 + countLessThan(root->right, key);
}
// �����ض���Χ [a, b) ����˷�Χ�ڵ�����Ԫ�صĸ���
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
