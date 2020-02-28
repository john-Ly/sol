#include <vector>

using namespace std;

struct BinaryNode {
    int data;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( int _data, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
        : data{ std::move( _data ) }, left{ lt }, right{ rt } { }
};

// @卡特兰数
// https://www.cnblogs.com/grandyang/p/4299608.html
// dp[i] = 表示有i个节点 可以形成的树的个数
// dp[0] = 1 空树  dp[1] = 左右子树 个数的乘积 1*1(两个空树)
int numTrees(int n) {
    vector<int> dp(n + 1);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] += dp[j] * dp[i - j - 1];  // (i-j-1) + j = i-1
        }
    }
    return dp[n];
}

// https://www.cnblogs.com/grandyang/p/4301096.html
// 如何使用记忆数组 @TODO

// 在给定范围内[1, n], 生成不同的 BST
vector<BinaryNode*> generateTrees(int n) {
    if (n == 0) return {};
    return helper(1, n);
}

vector<BinaryNode*> helper(int start, int end) {
    if (start > end) return {nullptr};
    vector<BinaryNode*> res;
    // 遍历每一个数字(都有可能成为根节点)  BST的中序遍历递增[1, n]
    for (int i = start; i <= end; ++i) {
        // 分为 左右 两个子树
        auto left = helper(start, i - 1), right = helper(i + 1, end);
        for (auto a : left) {
            for (auto b : right) {
                BinaryNode *node = new TreeNode(i);
                node->left = a;
                node->right = b;
                res.push_back(node);
            }
        }
    }
    return res;
}
