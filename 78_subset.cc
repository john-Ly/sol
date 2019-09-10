include <iostream>
#include <vector>
using namespace std;

// combination m from n.  // n: 元素总数量
// Picked: 已选元素的序号
// toPick: 还需选择的元素数量; 为0 全部组合
void pick(int n, int toPick, vector<int>& picked, vector<vector<int> >& res) {
    if(toPick == 0) {
        res.push_back(picked)
            return;
    }

    // 从1开始计数 (组合不能包含重复的项+按顺序生成)
    int smallest = picked.empty() ? 1 : picked.back() + 1;

    // 类似与DFS 但是不同@NOTE
    // 递归的思想是 只假设第一层的处理方案 递归调用 类似DFS直到最深层 关键是回溯环节
    for(int next=smallest; next<=n; ++next){
        picked.push_back(next);
        pick(n, picked, toPick-1);
        picked.pop_back();
    }
}

// https://leetcode.com/problems/subsets/discuss/27278/C%2B%2B-RecursiveIterativeBit-Manipulation
// 这个解答写的十分详细

// @TODO bit运算
// 思想: 有点类似计数器的思想  把每一个组合当作相应位是够占有  组合问题就是集合元素要么在 要么不在 二值
// 000
// 001
// 010
// 011

// 100
// 101
// 110
// 111
vector<vector<int>> subsets_bit(vector<int>& nums) {
    int n = nums.size();
    // 集合的幂集 2^n个 包含空集合
    int num = 1<<n;      // 0 0001 --> 1 0000
    vector<vector<int> > res(num);
    for(int i=0; i<num; i++) {    //从 1 循环到 2^n -1
        for(int j=0; j<n; j++) { // 对每一位进行比较
            int temp = i;
            // temp & (1<<j) 的结果要么是0 要么是1<<j
            if(temp & (1<<j))   //对应位上为1，则输出对应的字符
            res[i].push_back(nums[j]);
        }
        cout << "\n";
    }

    return res;
}

// https://www.cnblogs.com/grandyang/p/4309345.html
// https://leetcode.com/problems/subsets/discuss/27278/C%2B%2B-RecursiveIterativeBit-Manipulation
// 在原有子集的基础上进行叠加 -> 生成新的子集
vector<vector<int>> subsets_iteration(vector<int>& nums) {
    vector<vector<int> > res{{}};  // empty set
    for(int num : nums) {
        int n = res.size();
        for (int i=0; i<n; i++) {  // 这个是遍历res的集合元素的大小
            // 当前集合为 {[ ], [1]}   向集合添加2
            // 1. 首先复制 {[ ], [1], [ ], [1]}
            // 2. 末尾添加 {[ ], [1], [2], [1, 2]}
            res.push_back(res[i]);
            res.back().push_back(num);
        }
    }

    return res;
}

// 不过是dfs  深度优先  的确很符合递归的思想
// 1. 子问题就是  下一次函数的调用应该是已经生成subset
//   比如集合[1, 2, 3] 比如当前已经生成集合[[ ], [1]] 在调用递归函数 因该把剩下的元素的幂集合全部找到了
vector<vector<int>> subsets_recursive(vector<int>& nums) {
    vector<vector<int> > res{{}};  // empty set
    for(int num : nums) {
        int n = res.size();
        for (int i=0; i<n; i++) {  // 这个是遍历res的集合元素的大小
            // 当前集合为 {[ ], [1]}   向集合添加2
            // 1. 首先复制 {[ ], [1], [ ], [1]}
            // 2. 末尾添加 {[ ], [1], [2], [1, 2]}
            res.push_back(res[i]);
            res.back().push_back(num);
        }
    }

    return res;
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    dfs(nums, 0, path, res);
    return res;
}


/*  @TODO 递归的理解 还是有问题
                        []
                   /          \
                  /            \
                 /              \
              [1]                []
           /       \           /    \
          /         \         /      \
       [1 2]       [1]       [2]     []
      /     \     /   \     /   \    / \
  [1 2 3] [1 2] [1 3] [1] [2 3] [2] [3] []

  由于原集合每一个数字只有两种状态，要么存在，要么不存在，
  那么在构造子集时就有选择和不选择两种情况，所以可以构造一棵二叉树，左子树表示选择该层处理的节点，右子树表示不选择，最终的叶节点就是所有子集合
*/
void dfs(vector<int>& nums, int index, vector<int>& path, vector<vector<int>>& res) {
    res.push_back(path);
    for (unsigned int i = index; i < nums.size(); i++) {
        path.push_back(nums[i]);
        dfs(nums, i+1, path, res);
        path.pop_back();
    }
}
