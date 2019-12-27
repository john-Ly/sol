#include <iostream>
#include <queue>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4288151.html
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

// 基础解法
class Sol_level_nonrecursive {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        queue<Node*> Q;
        Q.push(root);
        while (!Q.empty()) {
            int size = Q.size();
            for (int i=0; i<size; ++i) {
                auto cur = Q.front();
                Q.pop();
                if (i < size-1) cur->next = Q.front();
                if (cur->left) Q.push(cur->left);
                if (cur->right) Q.push(cur->right);
            }
        }
        return root;
    }
};

class Sol_recursive {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        if (root->left) root->left->next = root->right;
        if (root->right) root->right->next = root->next ? root->next->left : nullptr;
        // 针对完全二叉树
        // 先处理左子树 不会遗漏
        connect(root->left);
        connect(root->right);
        return root;
    }

    // [2,1,3,0,7,9,1,2,null,1,0,null,null,8,8,null,null,null,null,7]
    Node* connect2(Node* root) {
        if (!root) return nullptr;
        auto p = root->next;
        // 取出与父节点 同层的next节点的孩子
        while (p) {
            if (p->left) {
                p = p->left;
                break;
            }
            if (p->right) {
                p = p->right;
                break;
            }
            p = p->next;
        }

        if (root->right) root->right->next = p;
        if (root->left) root->left->next = root->right ? root->right : p;
        // @TODO 并未理解 为什么可以  不清楚原因
        connect2(root->right);
        connect2(root->left);
        return root;
    }
};

// 联通每一层的节点 需要有上一层节点信息
// 完全二叉树
class Sol_constant {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        auto start = root;    // start标记每一层的起始节点
        Node* cur = nullptr;  // cur 遍历该层的节点

        while (start->left) {
            cur = start;
            while (cur) {
                cur->left->next = cur->right;
                if (cur->next) cur->right->next = cur->next->left;
                cur = cur->next;
            }
            start = start->left;
        }
        return root;
    }
};

// 非 完全二叉树
// https://www.cnblogs.com/grandyang/p/4290148.html
// 这种思路起始非常正常 比较直观
class Sol_const {
public:
    Node* connect(Node* root) {
        auto dummy = new Node(0);  // dummy 作为子层的 第一个节点(虚拟)
        auto cur = dummy;          // cur 作为子层的遍历iterator
        auto head = root;

        while (root) {
            // 1. 处理 root 左右孩子节点
            if (root->left) {
                cur->next = root->left;
                cur = cur->next;
            }
            if (root->right) {
                cur->next = root->right;
                cur = cur->next;
            }
            // 2. root 查找平行层的next
            root = root->next;
            if (!root) { // 当前层连接完毕
                cur = dummy;
                root = dummy->next;
                dummy->next = nullptr;
            }
        }

        delete dummy;
        return head;
    }
};