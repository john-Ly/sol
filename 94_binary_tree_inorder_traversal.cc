#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>

#include <cstdint>  // LONG_MIN
#include <limits>  // LONG_MIN
using namespace std;

// 前中后序 层次
// https://www.cnblogs.com/grandyang/p/4251757.html

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
    auto cur = root;
    while (cur || !st.empty()) {
        if(cur) {
            st.push(cur);
            cout << cur->data << ' ';
            cur = cur->left; // 会找到最左边节点
        } else {
            auto tmp = st.top(); st.pop();
            cur = tmp->right;
        }
    }
}

template <class T>
void PreorderNonRecursive2(BinaryNode<T> *root) {
	if(root == nullptr) return;
    stack<BinaryNode<T>*> st;
    st.push(root);
    // 这种思路更好理解: 针对每一个节点都当作根节点对待 压栈的顺序先是右节点, 左节点
    while (!st.empty()) {
        auto tmp = st.top(); st.pop();
        cout << tmp->data << ' ';
        if(tmp->right) st.push(tmp->right);
        if(tmp->left) st.push(tmp->left);
    }
}

template <class T>
void Inorder(BinaryNode<T> *root) {
	if(root == nullptr) return;

	Inorder(root->left);       //Visit left subtree
    cout << root->data << ' ';
	Inorder(root->right);      // Visit right subtree
}

// https://www.cnblogs.com/grandyang/p/4297300.html
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
void InorderNonRecursive2(BinaryNode<T> *root) {
    stack<BinaryNode<T>*> st;
    auto cur = root;
    while (cur || !st.empty()) {
        if(cur) {
            st.push(cur);
            cur = cur->left;
        } else {
            cur = st.top(); st.pop();
            cout << cur->data << ' ';  // treat as root again, next root->right
            cur = cur->right;
        }
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
void PostorderNonRecursive(BinaryNode<T> *root) {
	if(root == nullptr) return;
    stack<BinaryNode<T>*> st;
    vector<T> res;
    st.push(root);
    // 前序 顺序是 根-左-右; 后续: 根-右-左 ==> 左-右-根(头插法 保证逆序)
    while (!st.empty()) {
        auto tmp = st.top(); st.pop();
        res.insert(res.begin(), tmp->data);
        if(tmp->left) st.push(tmp->left);
        if(tmp->right) st.push(tmp->right);
    }
    std::ostream_iterator<T> out_it (std::cout, " ");
    std::copy(res.begin(), res.end(), out_it);
}

template <class T>
void PostorderNonRecursive2(BinaryNode<T> *root) {
    stack<BinaryNode<T>*> st;
    vector<T> res;
    auto cur = root;
    while (cur || !st.empty()) {
        if(cur) {
            st.push(cur);
            res.insert(res.begin(), cur->data);
            cur = cur->right;
        } else {
            auto tmp = st.top(); st.pop();
            cur = tmp->left;
        }
    }
    std::ostream_iterator<T> out_it (std::cout, " ");
    std::copy(res.begin(), res.end(), out_it);
}

// https://www.cnblogs.com/grandyang/p/4051321.html
// 递归写法暂时不考虑
template <class T>
void LevelOrder(BinaryNode<T> *root) {
	if(root == nullptr) return;
	queue<BinaryNode<T>*> Q;
	Q.push(root);
	while(!Q.empty()) {
        for(auto i=Q.size(); i>0; --i) {
            auto cur = Q.front(); Q.pop();
            cout << cur->data << " ";
            if(cur->left) Q.push(cur->left);
            if(cur->right) Q.push(cur->right);
        }
        cout << endl;
	}
}

template <class T>
void LevelOrderBottomUp(BinaryNode<T> *root) {
	if(root == nullptr) return;
    vector<vector<T>> vec;
	queue<BinaryNode<T>*> Q;
	Q.push(root);
	while(!Q.empty()) {
        vector<T> level;
        for(auto i=Q.size(); i>0; --i) {
            auto cur = Q.front(); Q.pop();
            level.push_back(cur->data);
            if(cur->left) Q.push(cur->left);
            if(cur->right) Q.push(cur->right);
        }
        vec.insert(vec.begin(), level);
	}

    for (const auto& res : vec) {
        ostream_iterator<T> out_it (std::cout, " ");
        copy(res.begin(), res.end(), out_it);
        cout<<"\n";
    }
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


// https://www.cnblogs.com/grandyang/p/4298435.html
// BST  左<根<右
// 但是有的题目 会要求 左<=根<右
template <class T, class T2 = int>
bool isValidBST(BinaryNode<T> *root, T2 min, T2 max) {
    if(!root) return true;
    if(root->data <= min || root->data >= max) return false;
    return isValidBST(root->left, min, root->data) && isValidBST(root->right, root->data, max);
}

// * &  传入指针的指针 (实际)
// 如果只是指针可能会造成拷贝
template <class T>
bool isValidBST(BinaryNode<T> *root, BinaryNode<T>*& pre) {
    if(!root) return true;

	bool le = isValidBST(root->left, pre);
    if(!le) return false;
    if(pre) {
        if(root->data <= pre->data) return false;
    }
    pre = root;
	return isValidBST(root->right, pre);
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
	cout<<"Preorder: \n";
	Preorder(root); cout<<"\n";
	PreorderNonRecursive(root); cout<<"\n";
	PreorderNonRecursive2(root); cout<<"\n";
	cout<<"Inorder recur+non: \n";
	Inorder(root); cout<<"\n";
	InorderNonRecursive(root); cout<<"\n";
	InorderNonRecursive2(root); cout<<"\n";
	cout<<"Postorder: \n";
	Postorder(root); cout<<"\n";
	PostorderNonRecursive(root); cout<<"\n";
	PostorderNonRecursive2(root); cout<<"\n";
	cout<<"Levelorder: \n";
    LevelOrder(root); cout<<"\n";
    LevelOrderBottomUp(root); cout<<"\n";


    cout << isValidBST(root, numeric_limits<char>::min(), numeric_limits<char>::max()) << endl;
    BinaryNode<char>* pre = nullptr;
    cout << isValidBST(root, pre) << endl;

    return 0;
}
