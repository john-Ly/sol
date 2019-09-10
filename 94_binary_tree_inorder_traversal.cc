#include <iostream>
#include <stack>
using namespace std;

template <class Comparable>
struct BinaryNode {
    Comparable data;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const Comparable& _data, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
        : data{ _data }, left{ lt }, right{ rt } { }

    BinaryNode( Comparable && _data, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
        : data{ std::move( _data ) }, left{ lt }, right{ rt } { }
};

template <class T>
void Preorder(BinaryNode<T> *root) {
	if(root == nullptr) return;

    cout << root->data << ' ';
	Preorder(root->left);     // Visit left subtree
	Preorder(root->right);    // Visit right subtree
}

template <class T>
void PreorderNonRecursive(BinaryNode<T> *root) {
    stack<BinaryNode<T>*> st;
	if(root == nullptr) return;

    cout << root->data << ' ';
	Preorder(root->left);     // Visit left subtree
	Preorder(root->right);    // Visit right subtree
}


template <class T>
void Inorder(BinaryNode<T> *root) {
	if(root == nullptr) return;

	Inorder(root->left);       //Visit left subtree
    cout << root->data << ' ';
	Inorder(root->right);      // Visit right subtree
}

template <class T>
void InorderNonRecursive(BinaryNode<T> *root) {
    stack<BinaryNode<T>*> st;
    auto cur = root;
    while (cur || !st.empty()) {
        while(cur) {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top(); st.pop();
        cout << cur->data << ' ';  // treat as root again, next root->right
        cur = cur->right;
    }
}

template <class T>
void Postorder(BinaryNode<T> *root) {
	if(root == nullptr) return;

	Postorder(root->left);    // Visit left subtree
	Postorder(root->right);   // Visit right subtree
    cout << root->data << ' ';
}

template <class T>
BinaryNode<T>* Insert(BinaryNode<T> *root, char data) {
	if(root == nullptr) {
		root = new BinaryNode<T>(data);
	}
	else if(data <= root->data)
		root->left = Insert(root->left, data);
	else
		root->right = Insert(root->right, data);
	return root;
}

// time complexity: O(n)
// space complexity:
//     O(h)
//     O(log n) -- best/avg
//     O(n) -- worst
int main() {
	/* BST
	            M
			   / \
			  B   Q
			 / \   \
			A   C   Z
    */
	BinaryNode<char>* root = nullptr;
	root = Insert(root,'M'); root = Insert(root,'B');
	root = Insert(root,'Q'); root = Insert(root,'Z');
	root = Insert(root,'A'); root = Insert(root,'C');
	cout<<"Preorder: ";
	Preorder(root);
	cout<<"\n";
	cout<<"Inorder recur+non: ";
	Inorder(root);
	cout<<"\n";
	InorderNonRecursive(root);
	cout<<"\n";
	cout<<"Postorder: ";
	Postorder(root);
	cout<<"\n";

    return 0;
}
