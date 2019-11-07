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
		// �� A[0..i-1] ���� A[i]
		int j = i;
		while(j>0 && A[j-1] > A[j]) {
			// ����ʽ a: A[j+1..i]����������Ԫ�ض����� A[j]
			// ����ʽ b: A[0..i]�����ڳ� A[j]�������Ԫ���Ѿ��ź���
			swap(A[j-1], A[j]);
			--j;
		}
	}
}

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

// ��ת�������� 
vector<int> solve(vector<int>& shifted) {
	int n = shifted.size();
	vector<int> ret;
	Node* candidates = nullptr;
	for(int i=0; i<n; ++i)
		candidates = insert(candidates, new Node(i+1));
	// �����һ��λ�ÿ�ʼ��� A[]
	for(int i=n-1; i>=0; --i) {
		// ���ڴ���ֵ�ĺ������ù��� larger��
		int larger = shifted[i];
		Node* k = kth(candidates, i+1-larger);
		ret[i] = k->key;
		candidates = erase(candidates, k->key);
	}
	return ret;
}

// �����������⣿���� 
int main() {
	vector<int> shifted{0, 1, 1, 2, 3};
	for(auto i : solve(shifted) )
      	cout << i << " ";
      	
	return 0;
}
