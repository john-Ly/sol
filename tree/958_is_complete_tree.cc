#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// https://cloud.tencent.com/developer/article/1339604
// 完全二叉树nullptr是出现在结尾, 如果非完全 一定是空洞 + 叶子
// @TODO leetcode 超时
bool is_complete(TreeNode *root) {
    queue<TreeNode*> q;
    // 进行广度优先遍历（层次遍历），并把NULL节点也放入队列
    q.push(root);
    while (!q.empty()) {
        for (int i=q.size(); i>=0; --i) {
            auto cur = q.front(); q.pop();
            if (!cur) continue;
            q.push(cur->left);
            q.push(cur->right);
        }
    }

    // 判断是否还有未被访问到的节点
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        // 访问到的的非nullptr节点，则树存在空洞，为非完全二叉树
        if (cur) {
            return false;
        }
    }
    return true;
}

 // 完全
 // complete binary tree
 //              M
 //    		   /  \
 //    		  B    Q
 //    		 / \   /
 //    		A  C  O

 //              M
 //    		   /  \
 //    		  B    Q
 //    		 /    /
 //    		A    O

 //              M
 //    		   /  \
 //    		  B    Q
 //    		      /
 //    		     O

 //              M
 //    		   /  \
 //    		  B
 //    		 /
 //    		O
// 无法处理最后一种情况
bool is_complete2(TreeNode *root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int level = q.size();
        bool hole = false;
        for (int i=0;  i < level; ++i) {
            auto cur = q.front(); q.pop();
            if (cur->left) {
                if (last) return false;
                q.push(cur->left);
                if (cur->right) { q.push(cur->right); }
                else { last = true; }
            } else if (cur->right) {
                return false;
            }
        }
    }
    return true;
}

// https://leetcode.com/problems/check-completeness-of-a-binary-tree/discuss/205682/JavaC%2B%2BPython-BFS-Level-Order-Traversal
// 跟第一种方法一样 不过更简洁

// For a complete binary tree,
// there should not be any node after we met an empty one.
// 遇到第一个空结点后 后面不应该再有非空结点
bool isCompleteTree(TreeNode* root) {
    vector<TreeNode*> bfs;
    bfs.push_back(root);
    int i = 0;
    while (i < bfs.size() && bfs[i]) {
        bfs.push_back(bfs[i]->left);
        bfs.push_back(bfs[i]->right);
        i++;
    }
    while (i < bfs.size() && !bfs[i])
        i++;
    return i == bfs.size();
}