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

// @NOTE 数据结构利用动画来进行理解
// time complexity: O(n)  每个节点最多被访问两次(包含回溯的过程)
// space complexity:
//  O(h)  树高
//     O(log n) -- best/avg
//     O(n) -- worst

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

// https://ghh3809.github.io/2018/08/06/morris-traversal
// 先序遍历的第一个是根节点, 栈会逐级回溯
// 从根开始遍历, 然后压栈左节点(方便在对应层级访问右节点)
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
            // 找到最左边节点后 回溯(利用栈)
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
// 从根开始遍历, 然后压栈左节点(方便在对应层级访问右节点)
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

/*
 1. 若节点还有左子树, 先把左子树访问完(符合中序遍历的顺序)
 2. 没有左子树, 访问最左节点, 并尝试访问右子树
 */
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

/*
  十分详细的morris遍历
  https://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html
  https://ghh3809.github.io/2018/08/06/morris-traversal/

 - 从根节点开始访问。
 - 如果当前节点C不存在左子树，按中序遍历的规则，应当访问节点C，并进入其右子树进行遍历。
 - 如果当前节点C存在左子树，就找到C的前驱节点B，并将B的右孩子指向C（存储后继），同时当前节点转入左子树进行遍历。
 - 步骤2中访问右子树时，如果节点本身没有右子树，则会直接转入其后继节点C。根据中序遍历的规则，说明此时C的左子树遍历完成。为了还原树结构，我们需要重新找到C的前驱节点，并将其右孩子设置为nullptr。之后我们访问节点C，并进入其右子树进行遍历。

 后继节点的计算方法(中序遍历转换)
 1. 对于存在右子树的节点A，其后继节点是其右子树中最左侧的节点；
 2. 对于没有右子树的节点B，其后继节点是其自下而上的父节点中第一个将其作为左子树的节点。

 虽然直接后继不好判断 可以通过根节点的左子树来判断是否是前驱(反向判断)


 时间复杂度为 O(n) 仅可能两次查找前驱节点
 */
template <class T>
vector<T> InorderMorris(BinaryNode<T> *root) {
    if (!root) return {};
    vector<T> res;
    auto cur = root; BinaryNode<T>* pre = nullptr;
    while (cur) {
        if (!cur->left) {  // 左子树不存在  访问+进入右节点
            res.push_back(cur->data);
            cur = cur->right;
        } else {
            // 判断前驱节点是否访问过: 是, 进入当前节点的右子树; 否 左子树
            pre = cur->left;
            //                      不判断 会死循环
            while (pre->right && pre->right != cur) pre = pre->right;
            if (!pre->right) { // 前驱节点未访问 存放后继节点
                pre->right = cur;
                cur = cur->left;
            } else {           // 前驱节点访问过了 恢复树的结构
                pre->right = nullptr;
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
    }
    return res;
}

template <class T>
vector<T> PreorderMorris(BinaryNode<T> *root) {
    if (!root) return {};
    vector<T> res;
    auto cur = root; BinaryNode<T>* pre = nullptr;
    while (cur) {
        if (!cur->left) {  // 左子树不存在  访问+进入右节点
            res.push_back(cur->data);
            cur = cur->right;
        } else {
            // 判断前驱节点是否访问过: 是, 进入当前节点的右子树; 否 左子树
            pre = cur->left;
            //                      不判断 会死循环
            while (pre->right && pre->right != cur) pre = pre->right;
            if (!pre->right) { // 前驱节点未访问 存放后继节点
                res.push_back(cur->val);
                pre->right = cur;
                cur = cur->left;
            } else {           // 前驱节点访问过了 恢复树的结构
                pre->right = nullptr;
                cur = cur->right;
            }
        }
    }
    return res;
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
    list<T> res;
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

// https://ghh3809.github.io/2018/08/06/morris-traversal/
// 后续遍历的思想就是用栈 保存(根 右 左)
// 由于后续遍历的回溯过程只可能上升一层，因此可以添加临时变量lastNode记录刚刚访问的节点，如果当前节点是上次访问节点的父节点，则说明子树访问完成，可以访问当前节点了。
/*
vector<int> postorderTraversal(TreeNode* root) {
    if(!root) return {};
    vector<int> vi;
    stack<TreeNode*> st;
    TreeNode* cur = nullptr;
    st.push(root);
    auto pre = root;
    while (!st.empty()) {
    auto cur = st.top(); st.pop();
    //   叶子节点                           孩子节点已经访问过了
    if((!cur->left && !cur->right) || (cur->left == pre || cur->right == pre)) {
        vi.push_back(cur->val);
        pre = cur;
    } else {
        st.push(cur);
        if(cur->right) st.push(cur->right);
        if(cur->left) st.push(cur->left);
    }
    }
    return vi;
}
*/

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

// 等于的情况 不插入
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
// @TODO 这种做法需要一个更大的类型进行比较(比如int -> long)
template <class T, class T2 = int>
bool isValidBST(BinaryNode<T> *root, T2 min, T2 max) {
    if(!root) return true;
    if(root->data <= min || root->data >= max) return false;
    return isValidBST(root->left, min, root->data) && isValidBST(root->right, root->data, max);
}

// * &  传入指针的指针 (实际)
// 如果只是指针可能会造成拷贝
// 实际中序遍历
// @TODO 理解不了递归
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

// 如果递归不太理解还是 不要勉强
bool isValidBST(TreeNode* root) {
    stack<TreeNode*> st;
    auto cur = root;
    auto preValue = numeric_limits<long>::min();
    while( cur || !st.empty() ) {
        while(cur) {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top(); st.pop();
        if(cur->val <= preValue) return false;
        preValue = cur->val;
        cur = cur->right;
    }
    return true;
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

// 该函数应该不能用来计算树高度
template <class T>
int HeightofTree_DFS(BinaryNode<T> *root) {
	if(!root) return 0;
    auto lHeight = HeightofTree_DFS(root->left);
    if(lHeight == -1) return -1;
    auto rHeight = HeightofTree_DFS(root->right);
    if(rHeight == -1) return -1;
    if(lHeight - rHeight > 1 || lHeight - rHeight < -1) return -1;
	return max(lHeight, rHeight) + 1;
}

// https://leetcode.com/problems/balanced-binary-tree/discuss/35691/The-bottom-up-O(N)-solution-would-be-better
// 1.top down
template <class T>
bool isBalanced(BinaryNode<T> *root) {
    // height depth 的起始定义不同  depth会定义成0
	if(!root) return true;
    auto tmp = HeightofTree(root->left) - HeightofTree(root->right);
    if(tmp > 1 || tmp < -1) return false;
	return isBalanced(root->left) && isBalanced(root->right);
}

// 2. bottom up
template <class T>
bool isBalanced(BinaryNode<T> *root) {
    return HeightofTree_DFS(root) != -1;
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

// Two binary trees are considered the same:
// they are structurally identical and the nodes have the same value.
// 问题是什么; 子问题是什么
// https://www.cnblogs.com/grandyang/p/4053384.html
template <class T>
bool isSameBinaryTree(BinaryNode<T> *p, BinaryNode<T> *q) {
    if (!p && !q) return true;
    if ((p && !q) || (!p && q) || (p->data != q->data)) return false;
    return isSameBinaryTree(p->left, q->left) && isSameBinaryTree(p->right, q->right);
}

template <class T>
bool isSameNonRecursive(BinaryNode<T> *p, BinaryNode<T> *q) {
	if(!p && !q) return true;
	queue<BinaryNode<T>*> Q1, Q2;
	Q1.push(p);	Q2.push(q);
	while(!Q1.empty() && !Q2.empty()) {
        auto cur1 = Q1.front(); Q1.pop();
        auto cur2 = Q2.front(); Q2.pop();
        if(!cur1 && !cur2) continue;
        if ((cur1 && !cur2) || (!cur1 && cur2) || (cur1->data != cur2->data)) return false;
        Q1.push(cur1->left);
        Q1.push(cur1->right);
        Q2.push(cur2->left);
        Q2.push(cur2->right);
	}
    return true;
}

// https://www.cnblogs.com/grandyang/p/4051715.html
template <class T>
T isSymmetricBinaryTree(BinaryNode<T> *p, BinaryNode<T> *q) {
    if (!p && !q) return true;
    if ((p && !q) || (!p && q) || (p->data != q->data)) return false;
    // diff with isSame()
    return isSymmetricBinaryTree(p->left, q->right) && isSymmetricBinaryTree(p->right, q->left);
}

// 判断是否对称
template <class T>
bool isSymmetric(BinaryNode<T> *root) {
    if (!root) return true;
    return isSymmetricBinaryTree(root->left, root->right);
}

template <class T>
bool isSymmetricNonRecursive(BinaryNode<T> *root) {
	if(!root) return true;
	queue<BinaryNode<T>*> Q1, Q2;
	Q1.push(root->left);
	Q2.push(root->right);
    // 不同于levelOrder
	while(!Q1.empty() && !Q2.empty()) {
        auto cur1 = Q1.front(); Q1.pop();
        auto cur2 = Q2.front(); Q2.pop();
        if(!cur1 && !cur2) continue;
        if ((cur1 && !cur2) || (!cur1 && cur2) || (cur1->data != cur2->data)) return false;
        Q1.push(cur1->left);
        Q1.push(cur1->right);
        Q2.push(cur2->right);
        Q2.push(cur2->left);
	}
    return true;
}

// https://www.cnblogs.com/grandyang/p/4295245.html
// 想到利用AVL树 平衡的性质 但是太难了
template <class T>
BinaryNode<T>* sortedArrayToBST(vector<T>& nums, size_t lo, size_t hi) {
    if(lo >= hi) return nullptr;
    auto mid = (hi-lo)/2 + lo;
    BinaryNode<T> * root = new BinaryNode<T>(nums[mid]);
    root->left = sortedArrayToBST(nums, lo, mid);
    root->right = sortedArrayToBST(nums, mid+1, hi);
    return root;
}

namespace {
    template<class T>
    struct ListNode {
        T val;
        ListNode *next;
        ListNode(T x) : val(x), next(nullptr) {}
    };
}

// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/solution/
// 递归版本的时间复杂度 (数组)  值得复习
// 方法二: 将链表转换成数组 这样不用每次计算中间节点
template <class T>
BinaryNode<T>* sortedListToBST(ListNode<T>* head) {
    if (!head) return nullptr;            // 无节点
    if (!head->next) return new BinaryNode<T>{head->val};  // 只有一个节点
    auto fast = head, slow = head;
    auto last = slow;
    while(fast->next && fast->next->next) {
        last = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    // 可以认为slow处于中点处, 断开链表
    fast = slow->next;
    last->next = nullptr;

    BinaryNode<T> * root = new BinaryNode<T>(slow->val);
    if(slow != head)
        root->left = sortedListToBST(head);
    root->right = sortedListToBST(fast);
    return root;
}

// 方法三:
// 类似有序数组的方法 同样使用递归 但是每次只处理当前根节点(不需要计算mid)
// 思想是使用中序遍历 函数调用的顺序被改变了


// 分解子问题
//  hasPathSum(root, sum) = 从root出发, 是否有一条路径上的节点和等于sum
//  hasPathSum(root, sum) = root->data + root->left or root->right是否有一条路径节点等于sum-root->data
template <class T>
bool hasPathSum(BinaryNode<T>* root, T sum) {
    // 初始部分
    if (!root) return false;            // 无节点
    if (root->data == sum && !root->left && !root->right) return true; // 只有一个节点
    return hasPathSum(root->left, sum - root->data) || hasPathSum(root->right, sum - root->data);
}

// 找到所有可能的路径
// 可以理解为一个棋盘
// @TODO DFS + DP
template <class T>
vector<vector<T>> PathSum(BinaryNode<T>* root, T sum) {
    vector<vector<T> > paths;
    vector<T> path;
    findPaths(root, sum, path, paths);
    return paths;
}

template <class T>
void findPaths(BinaryNode<T>* root, T sum, vector<T>& path, vector<vector<T> > paths) {
    // 到达最后一行 即叶子节点
    if(!root) return;
    // 回溯算法
    path.push_back(root->data);
    // 找到了完整的路径
    if (!(root->left) && !(root->right) && sum == root->val)
        paths.push_back(path);
    findPaths(root->left, sum - root->data, path, paths);
    findPaths(root->right, sum - root->data, path, paths);
    path.pop_back();
}

// https://www.cnblogs.com/grandyang/p/4293853.html
// 二叉树 按照前序的方式 生成链表(bottom up)
template <class T>
void flatten(BinaryNode<T>* root) {
    // 异常
    if(!root) return;

    // 递归到左右子树
    if(root->left) flatten(root->left);
    if(root->right) flatten(root->right);

    // 左右子树都完成flatten操作后
    /*
            root          root
            /   \         /  \
         left  right    nul   left
                                 \
                                 right
     */
    BinaryNode<T>* tmp = root->right;
    root->right = root->left;
    root->left = nullptr;
    while(root->right) root=root->right;
    root->right = tmp;
}

//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/discuss/37010/Share-my-simple-NON-recursive-solution-O(1)-space-complexity!
// 的确利用了 morris的方法 找到根节点的的前驱节点
template <class T>
void flatten_morris(BinaryNode<T> *root) {
    if (!root) return;
    auto cur = root;
    while (cur) {
        if (cur->left) {  // 左子树存在
            auto pre = cur->left;
            //  找到cur节点的左子树的最右的节点
            while (pre->right) pre = pre->right;
            pre->right = cur->right;
            cur->right = cur->left;
            cur->left = nullptr;
        }
        cur = cur->right;
    }
    return res;
}

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
    {
        vector<int> inorder{9, 10, 12, 16, 27, 36, 54, 72};
        auto root = sortedArrayToBST(inorder, 0, inorder.size());
        cout<<"sorted vec to BST \n";
        Inorder(root); cout<<"\n";
    }

    return 0;
}
