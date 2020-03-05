#include <vector>
#include <algorithm>
#include <climit>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4298069.html
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


namespace sol_valid_bst {

// 如果递归不太理解还是 不要勉强
// 中序遍历
bool isValidBST(TreeNode* root) {
    stack<TreeNode*> st;
    auto cur = root;
    // preValue 保存中序遍历的前驱
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
}

// 判断序列是否属于bst的前序
bool verifyPreorder(vector<int>& preorder) {
    int low = INT_MIN;
    stack<int> s;
    // s.top() 表示cur 根节点
    for (auto a : preorder) {
        if (a < low) return false;

        // 采用while循环 确定a是哪一个根的右孩子
        while (!s.empty() && a > s.top()) {
            low = s.top(); s.pop();
        }
        s.push(a);
    }
    return true;
}

// 判断序列是否属于bst的前序
bool verifyPostorder(vector<int>& postorder) {
    int upper = INT_MAX;
    stack<int> s;
    // s.top() 表示cur 根节点
    // 后续遍历 -> reverse -> 根 右 左; 其余思路同上
    for (int i=postorder.size()-1; i>=0; --i) {
        if (postorder[i] > upper) return false;

        while (!s.empty() && postorder[i] < s.top()) {
            upper = s.top(); s.pop();
        }
        s.push(postorder[i]);
    }
    return true;
}