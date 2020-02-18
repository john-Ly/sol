#include <algorithm>
using namespace std;

struct BinaryNode {
    int val;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(int _data, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
        : data{std::move(_data)}, left{lt}, right{rt} { }
};


// https://www.cnblogs.com/grandyang/p/4640572.html
BinaryNode* lowestCommonAncestor(BinaryNode* root,
                                 BinaryNode* p, BinaryNode* q) {
    if (!root) return nullptr;

    if (root->val > std::max(p->val, q->val))
        return lowestCommonAncestor(root->left, p, q);
    else if (root->val < std::min(p->val, q->val))
        return lowestCommonAncestor(root->right, p, q);
    else return root;

    // while (true) {
    //     if (root->val > max(p->val, q->val)) root = root->left;
    //     else if (root->val < min(p->val, q->val)) root = root->right;
    //     else break;
    // }
    // return root;
}

// 更一般的Binary Tree 不考虑
// https://www.cnblogs.com/grandyang/p/4641968.html