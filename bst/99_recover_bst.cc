#include <vector>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4298069.html
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 仅有两个节点违背了中序关系
// 需要额外的数组 不改变树的结构
class Sol1 {
public:
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> list;
        vector<int> vals; // 存储中序结果
        inorder(root, list, vals);
        sort(vals.begin(), vals.end());
        for (int i = 0; i < list.size(); ++i) {
            list[i]->val = vals[i];
        }
    }

private:
    void inorder(TreeNode* root, vector<TreeNode*>& list, vector<int>& vals) {
        if (!root) return;
        inorder(root->left, list, vals);
        list.push_back(root);
        vals.push_back(root->val);
        inorder(root->right, list, vals);
    }
};


// e.g.:  6, 3, 4, 5, 2
//        -f          -s
//
//
// [5,3,9,-2147483648,2]
// [5,2,9,...,3]
// https://leetcode.com/problems/recover-binary-search-tree/discuss/32535/No-Fancy-Algorithm-just-Simple-and-Powerful-In-Order-Traversal
class Sol2 {
public:
    TreeNode *first = nullptr, *second = nullptr;
    TreeNode *pre = new TreeNode(numeric_limits<int>::min());

    void recoverTree(TreeNode* root) {
        inorder(root);
        swap(first->val, second->val);
    }

private:
    // 中序遍历 会有降序产生
    // 第一个错误结点: 第一次降序 较大的结点
    // 第二个错误结点: 最后一次降序 较小的结点
    // a. 1 2 3 4 5
    //    1 2 4 3 5   只有一次降序
    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        // 中序遍历 递归  O(n) space
        if(!first && pre->val >= root->val) first = pre;
        if(first && pre->val >= root->val) second = root;
        pre = root;

        inorder(root->right);
    }
};

// @TODO morris
