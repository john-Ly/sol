#include <iostream>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

// path_sum 1 (判断是否有满足条件的路径)
// https://www.cnblogs.com/grandyang/p/4036961.html
// 分解子问题
//  hasPathSum(root, sum) = 从root出发, 是否有一条路径上的节点和等于sum
//  hasPathSum(root, sum) = root->left or root->right是否有一条路径节点等于sum-(root->data)
namespace path1 {
bool hasPathSum_recursive(TreeNode* root, int sum) {
    // 初始部分
    if (!root) return false;            // 无节点
    if (root->data == sum && !root->left && !root->right) return true; // 只有一个节点
    return hasPathSum(root->left, sum - root->data) || hasPathSum(root->right, sum - root->data);
}

// 会改变原来节点的值 @TODO
bool hasPathSum_iterative(TreeNode* root, int sum) {
	if(!root) return false;
    stack<TreeNode*> st;
    st.push(root);
    // 这种思路更好理解: 针对每一个节点都当作根节点对待 压栈的顺序先是右节点, 左节点
    while (!st.empty()) {
        auto t = st.top(); st.pop();
        if (!t->left && !t->right) {
            if (t->val == sum) return true;
        }
        if (t->right) {
            t->right->val += t->val;
            st.push(t->right);
        }
        if (t->left) {
            t->left->val += t->val;
            st.push(t->left);
        }
    }
    return false;
}
}

namespace path2 {
// https://www.cnblogs.com/grandyang/p/4042156.html
vector<vector<int>> PathSum(TreeNode* root, int sum) {
    vector<vector<int> > paths;
    vector<int> path;
    findPaths(root, sum, path, paths);
    return paths;
}

//       5
//      / \
//     4   8
//    /   / \
//   11  13  4
//  /  \    / \
// 7    2  5   1
// 回溯的方式  5_4_11_7   前面三个节点还保留在vector里面
//                   _2

// 符合前序遍历的顺序
// 5
// 4
// 11
// 7
// 2
// 8
// 13
// 4
// 5
// 1

void findPaths(TreeNode* root, int sum,
               vector<int>& path, vector<vector<int> >& paths) {
    // 到达最后一行 即叶子节点
    if(!root) return;
    // 回溯算法
    // cout << root->data << '\n';
    path.push_back(root->data);  // 默认每次直接添加
    // 找到了完整的路径
    if (!(root->left) && !(root->right) && sum == root->val)
        paths.push_back(path);
    findPaths(root->left, sum - root->data, path, paths);
    findPaths(root->right, sum - root->data, path, paths);
    path.pop_back();  // 找到的路径不符合 pop_back最后一个
}
}

namespace path3 {
// https://www.cnblogs.com/grandyang/p/6007336.html
// dfs + backtracking
int pathSum(TreeNode* root, int sum) {
    int res = 0;
    vector<TreeNode*> out;
    helper(root, sum, 0, out, res);
    return res;
}

// @param curSum 树中目前遍历节点路径的总和(每一次调用 curSum都不一样 代表了一种状态)
// out 代表当前遍历情况下 保存的节点个数(与curSum一一对应)
void helper(TreeNode* node, int sum, int curSum, vector<TreeNode*>& out, int& res) {
    if (!node) return;
    curSum += node->val;
    out.push_back(node);

    if (curSum == sum) ++res;
    int t = curSum;
    // curSum 会处理为0 的情况, 所以不应该把所有节点清空 保留一个
    // 只有1个节点  1 sum=0时,  全部清空会造成错误结果 @TODO
    for (int i = 0; i < out.size() - 1; ++i) {
        t -= out[i]->val;
        if (t == sum) ++res;
    }

    helper(node->left, sum, curSum, out, res);
    helper(node->right, sum, curSum, out, res);
    out.pop_back();
}

class sol_2 {
// 题目要求在二叉树中 找到路径和为sum的路径条数(只能从上到下 不用从根或叶子起始)
// hash_map[key, value]   curSum -> 路径的个数
// @TODO
int pathSum(TreeNode* root, int sum) {
    unordered_map<int, int> m;
    m[0] = 1;
    return helper(root, sum, 0, m);
}

int helper(TreeNode* node, int sum, int curSum, unordered_map<int, int>& m) {
    if (!node) return 0;
    curSum += node->val;
    int res = m[curSum - sum];
    ++m[curSum];
    res += helper(node->left, sum, curSum, m) + helper(node->right, sum, curSum, m);
    --m[curSum];
    return res;
}
};
}

// 虽然使用BFS+回溯 但是字符串末尾添加和删除 比较麻烦(往往是char粒度 而不是string粒度)
//    1
//  /   \
// 2     3
//  \
//   5
// ["1->2->5", "1->3"]
namespace bt_path_257 {
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    if (root) helper(root, "", res);
    return res;
}
void helper(TreeNode* node, string out, vector<string>& res) {
    if (!node->left && !node->right) res.push_back(out + to_string(node->val));
    // 1. 递归之前判断非空
    // 2. out+ string + "->" 形式 一方面避免了 之前回溯还要pop_back 因为传的是引用; 另一方面 ->的个数满足要求
    if (node->left) helper(node->left, out + to_string(node->val) + "->", res);
    if (node->right) helper(node->right, out + to_string(node->val) + "->", res);
}


// @TODO
// https://www.cnblogs.com/grandyang/p/4738031.html
vector<string> binaryTreePaths_1(TreeNode* root) {
    if (!root) return {};
    if (!root->left && !root->right) return {to_string(root->val)};
    vector<string> left = binaryTreePaths(root->left);
    vector<string> right = binaryTreePaths(root->right);
    left.insert(left.end(), right.begin(), right.end());
    for (auto &a : left) {
        a = to_string(root->val) + "->" + a;
    }
    return left;
}
}

// https://www.cnblogs.com/grandyang/p/4280120.html
// @SEE 53 maximum_subarray.cc
// 最大子数组之和  数组是线性的结构 因此可以用循环遍历
// maxAt(i) = max(0, maxAt(i-1)) + A[i]
//            filter the negative sum

// 二叉树 递归定义的
namespace bt_maximum_path_sum_124 {

int maxPathSum(TreeNode* root) {
    int res = INT_MIN;
    helper(root, res);
    return res;
}

// helper(node) = 以node为根节点时, 返回 path之和较大的(左边孩子还是右边孩子)
//  -10
//  / \
// 9  20
//   /  \
//  15   7
// 20-15-7 = 42
//  return the max-value-ended-at-root-node
int helper(TreeNode* node, int& res) {
    if (!node) return 0;
    // left/right 需要过滤掉负数的情况
    int left = max(helper(node->left, res), 0);
    int right = max(helper(node->right, res), 0);

    // 更新全局最大值(这个路径 ^形状)
    res = max(res, left + right + node->val);
    return max(left, right) + node->val;
}

}

// 参考257 然后将string 转化为int 但是有点开销
namespace sum_root_to_leaf_nums_129 {

// https://www.cnblogs.com/grandyang/p/4273700.html
int sumNumbers(TreeNode* root) {
    return dfs(root, 0);
}

// @TODO dfs 递归 什么时候用引用 什么时候传值
// dfs(node) = node为根节点是 所有的和
int dfs(TreeNode* root, int sum) {
    if (!root) return 0;

    // 前序遍历
    sum = sum * 10 + root->val;
    if (!root->left && !root->right) return sum;
    // 同层级的节点可以直接相加
    return dfs(root->left, sum) + dfs(root->right, sum);
}

// 先序遍历
// 祖先节点 都要*10倍
int sumNumbers_iterative(TreeNode* root) {
	if(!root) return 0;
    int res = 0;
    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        auto t = st.top(); st.pop();
        if (!t->left && !t->right) {
            res += t->val;
        }
        if (t->right) {
            t->right->val += (10 * t->val);
            st.push(t->right);
        }
        if (t->left) {
            t->left->val += (10 * t->val);
            st.push(t->left);
        }
    }
    return res;
}

}