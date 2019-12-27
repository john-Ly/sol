#include <iostream>
#include <queue>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4288151.html
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
};


// @SEE 116 怎么实现while循环就可以所有节点的遍历
// 层次遍历即可 @TODO怎么使用常量空间
class Solution_normal {
public:
    // 非完全二叉树 怎么处理
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            res.push_back(q.back()->val);
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode *node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return res;
     }
};

// https://leetcode.com/problems/binary-tree-right-side-view/discuss/56003/My-C%2B%2B-solution-modified-preorder-traversal
class Solution_recursive {
public:
    // 非完全二叉树 怎么处理
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        helper(root, 1, res);
        return res;
    }

    // 还是要遍历所有节点 才可以
    void helper(TreeNode *root, int level, vector<int> &res) {
        if(!root) return ;
        if(res.size()<level) res.push_back(root->val);
        helper(root->right, level+1, res);
        helper(root->left, level+1, res);
    }
};
