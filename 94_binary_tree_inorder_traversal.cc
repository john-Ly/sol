#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>

#include <cstdint>  // LONG_MIN
#include <cassert>
#include <limits>  // LONG_MIN
using namespace std;

// 二叉树左右子树有顺序
// 前中后序(主要是根节点的顺序) 层次
// https://www.cnblogs.com/grandyang/p/4251757.html
//
/* 中序遍历可以知道根的左右是否存在子树,  层次/先序/后序 可以确定根的位置
给定 先序+中序 or 后序+中序 可以唯一确定一颗二叉树
而 先序+后序 不能
	  A
	 /
	B
前序遍历： AB, 后序遍历： BA
	A
	 \
	  B
前序遍历： AB, 后序遍历： BA
*/

/*
 满
 full binary tree
	             M
			   /  \
			  B    Q
			 / \   /\
			A  C  O  Z

 完全
 complete binary tree
	             M
			   /  \
			  B    Q
			 / \   /
			A  C  O

 异常
	            M
			   / \
			  B   Q
			 / \   \
			A   C   Z
 */

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
// https://www.cnblogs.com/grandyang/p/4620012.html  返回第k小的元素(二叉树中序)
template <class T>
void InorderNonRecursive(BinaryNode<T> *root) {
    // int cnt = 0;
    stack<BinaryNode<T>*> st;
    auto cur = root;
    while (cur || !st.empty()) {
        while(cur) {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top(); st.pop();
        // ++cnt;
        // if(cnt == k) return cur->data;
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
// 层次遍历求平均值
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

// level表示当前的深度(表示层级) + DFS
// https://www.cnblogs.com/grandyang/p/4051326.html
template <class T>
void LevelOrderRecursive(BinaryNode<T> *root, int level, vector<vector<T>>& res) {
	if(root == nullptr) return;
    if(res.size() == level) res.push_back({});
    res[level].push_back(root->data);
    if(root->left) LevelOrderRecursive(root->left, level+1, res);
    if(root->right) LevelOrderRecursive(root->right, level+1, res);
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

// zigzag(curleve: left_right; next: right_left)
// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/discuss/33825/c%2B%2B-5ms-version%3A-one-queue-and-without-reverse-operation-by-using-size-of-each-level
// https://www.cnblogs.com/grandyang/p/4297009.html   递归思路 基本是层次递归的延伸 判断下层数的奇偶即可
template <class T>
void zigzagLevelOrder(BinaryNode<T> *root, vector<vector<T>>& res) {
	if(root == nullptr) return;
	queue<BinaryNode<T>*> Q;
	Q.push(root);
    bool leftToRight = true;

	while(!Q.empty()) {
        // queue的大小在循环中一直在变化 所以不要写成i=0; 可以考虑下面的方式
        int levelSize = Q.size();
        vector<T> row(levelSize);
        for(int i=0; i<levelSize; ++i) {
            auto cur = Q.front(); Q.pop();
            int idx = leftToRight ? i : levelSize - i -1;
            row[idx] = cur->data;
            if(cur->left) Q.push(cur->left);
            if(cur->right) Q.push(cur->right);
        }
        leftToRight = !leftToRight;
        res.push_back(row);
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
// 实际中序遍历
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

template <class T>
int count(BinaryNode<T>* node) {
    if (!node) return 0;
    return 1 + count(node->left) + count(node->right);
}

// find height of a binary tree
/*
    @NOTE
    depth of node = number of edges in path from root to that node
    depth深度 leetcode题目理解成 root到叶子节点路径之间节点的个数
    height 高度 与树的平衡有关

    depth = distance from root
    height = distance from the longest leaf

    height of tree = height of root = max depth
    height of tree with 1 node = 0   w.r.t level
    height of empty tree = -1;
*/

template <class T>
int HeightofTree(BinaryNode<T> *root) {
    // height depth 的起始定义不同  depth会定义成0
	if(!root) return -1;
	return max(HeightofTree(root->left), HeightofTree(root->right)) + 1;
}

// 层次遍历的层数即是maxDepth
template <class T>
int maxDepth(BinaryNode<T> *root) {
	if(!root) return 0;
	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

// [1, 2] 输出minDepth=2  因为定义如此(根节点肯定不可能是leaf)
// @NOTE maxDepth 题意要求 最大的depth 不可能考虑到根节点作为leaf
//       minDepth 则会退化到 根节点的问题
template <class T>
int minDepth(BinaryNode<T> *root) {
	if(!root) return 0;
    // 下面两句区别与maxDepth 主要是判断是否是leaf节点
    if (!root->left) return 1 + minDepth(root->right);
    if (!root->right) return 1 + minDepth(root->left);
	return min(minDepth(root->left), minDepth(root->right)) + 1;
}

template <class T>
int maxDepth2(BinaryNode<T> *root) {
	if(!root) return 0;
	queue<BinaryNode<T>*> Q;
	Q.push(root);
    int level = 0;
	while(!Q.empty()) {
        ++level;
        for(auto i=Q.size(); i>0; --i) {
            auto cur = Q.front(); Q.pop();
            if(cur->left) Q.push(cur->left);
            if(cur->right) Q.push(cur->right);
        }
	}
    return level;
}

// https://www.cnblogs.com/grandyang/p/4042168.html
template <class T>
int minDepth2(BinaryNode<T> *root) {
	if(!root) return 0;
	queue<BinaryNode<T>*> Q;
	Q.push(root);
    int level = 0;
	while(!Q.empty()) {
        ++level;
        for(auto i=Q.size(); i>0; --i) {
            auto cur = Q.front(); Q.pop();
            // 层次遍历找到第一个叶子节点 可以返回 (最短路径问题)
            if(!cur->left && !cur->right) return level;
            if(cur->left) Q.push(cur->left);
            if(cur->right) Q.push(cur->right);
        }
	}
    return -1;
}

// @TODO
// 如果BST增删十分频繁 求kth也频繁  怎么优化
// https://www.cnblogs.com/grandyang/p/4620012.html  : 重新设计BST的结构
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/solution/  : 使用LRU
template <class T>
T kthSmallest(BinaryNode<T> *root, int k) {
    // @fixme: should return invalid number, e.g. T==int, Return numeric_limits<long>::min()
    if(!root) return {};
    int cnt = count(root->left);
	if(k <= cnt)
		return kthSmallest(root->left, k);
	else if(k > cnt+1)
		return kthSmallest(root->right, k-cnt-1);
	else
        return root->data;
}

// Two binary trees are considered the same if they are structurally identical and the nodes have the same value.
// 问题是什么; 子问题是什么
template <class T>
T isSameBinaryTree(BinaryNode<T> *p, BinaryNode<T> *q) {
    if (!p && !q) return true;
    if ((p && !q) || (!p && q) || (p->val != q->val)) return false;
    return isSameBinaryTree(p->left, q->left) && isSameBinaryTree(p->right, q->right);
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
	root = Insert(root,'Q');// root = Insert(root,'Z');
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
    {
        vector<vector<char>> vec;
        LevelOrderRecursive(root, 0, vec);
        for (const auto& res : vec) {
            ostream_iterator<char> out_it (std::cout, " ");
            copy(res.begin(), res.end(), out_it);
            cout<<"\n";
        }
        cout<<"\n";
    }
    {
        cout<<"zigzagLevelOrder\n";
        vector<vector<char>> vec;
        zigzagLevelOrder(root, vec);
        for (const auto& res : vec) {
            ostream_iterator<char> out_it (std::cout, " ");
            copy(res.begin(), res.end(), out_it);
            cout<<"\n";
        }
        cout<<"\n";
    }

    cout << isValidBST(root, numeric_limits<char>::min(), numeric_limits<char>::max()) << endl;
    BinaryNode<char>* pre = nullptr;
    cout << isValidBST(root, pre) << endl;

    cout << "kth Smallest: " << kthSmallest(root, 7) << endl;

    {
        cout<<"maxDepth\n";
        auto t1 = maxDepth(root);
        auto t2 = maxDepth2(root);
        assert(t1 == t2);
        cout << t1 <<"\n";
    }
    {
        cout<<"minDepth\n";
        auto t1 = minDepth(root);
        auto t2 = minDepth2(root);
        assert(t1 == t2);
        cout << t1 <<"\n";
    }

    return 0;
}
