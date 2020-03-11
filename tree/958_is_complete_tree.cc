#include <queue>
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
        for (int i=q.size(); (q.front() !=nullptr && i>=0); --i) {
            auto cur = q.front(); q.pop();
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