#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{\n";
	for (vector<T> row: mat) {
        cout << "  [";
		for (T val: row) {
			cout << val << ',';
		}
        cout << "],\n";
	}
    cout << "}\n";
}

// combination m from n.  组合数
namespace combination {
//  n=4 先挑出 1, 求后三位
//  for (int i=0; i<n; ++i) {
//      for (int j=i+1; j<n; ++j) {
//          for (int k=j+1; k<n; ++k) {
//              for (int l=k+1; l<n; ++l) {
//      cout << i << "-" << j << "-" << k << "-" << l << endl;
// }}}}

// n: 元素总数量
// Picked: 已选元素的序号
// toPick: 还需选择的元素数量; 为0 全部组合
void pick(int n, int toPick, vector<int>& picked, vector<vector<int> >& res) {
    if(toPick == 0) { res.push_back(picked); return; }
    // 从1开始计数 (组合不能包含重复的项(之前已经选过了)+按顺序生成)
    int smallest = picked.empty() ? 1 : picked.back() + 1;

    for(int next=smallest; next<=n; ++next){
        picked.push_back(next);
        pick(n, picked, toPick-1);
        picked.pop_back();
    }
}

// 元素互不相同
// 题型1(2的特例): 从[0, m-1] 选出 n个数   数的范围也是 [0, m-1]
// 重复元素调用next_perm 就是组合combination

// 题型2: 从数组(size=m)中 选出 n个数组合
void combination_vector(vector<int>& v, int n) {
    int m = v.size();
    assert(n <= m);
    std::vector<int> pick(m, 0);
    for (int i=0; i<n; ++) pick[i] = 1;

    int count = 0;
    do
    {
        ++count;
        for (auto i : pick) {
            if (i)
                std::cout << values[i] << ", ";
        }
        std::cout << std::endl;
    } while (prev_permutation(pick.begin(), pic.end()));
}

// 题型3: 数组shuffle @TODO

}

// 选出集合 子集合的个数  幂集(不包括空集)
namespace subset {
// 集合的幂集 2^n个 包含空集合
// https://leetcode.com/problems/subsets/discuss/27278/C%2B%2B-RecursiveIterativeBit-Manipulation
// 思想: 类似计数器每次累加一位
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
        for (int i=0; i<res.size(); i++) {
            // 当前集合为 {[ ], [1]}   向集合添加2
            // 1. 首先复制 {[ ], [1], [ ], [1]}
            // 2. 末尾添加 {[ ], [1], [2], [1, 2]}
            res.push_back(res[i]);
            res.back().push_back(num);
        }
    }

    return res;
}

// https://www.cnblogs.com/grandyang/p/4310964.html
// 在原有子集的基础上进行叠加 -> 生成新的子集
// 集合可能存在重复数字  [1, 2, 2, 2]
// 1st-2: {[], [1], [2], [1,2]}
// 2nd-2: 只能加在集合的后两个{[], [1], [2], [1,2]}
// 3rd-2: 也只能加在集合的后两个{[], [1], [2], [1,2]}
vector<vector<int>> subsets_iteration_dup(vector<int>& nums) {
    if(nums.empty()) return {}; // 空集直接返回
    vector<vector<int> > res{{}};  // empty set
    // 排序之后可以把相同元素全部集中在一起
    std::sort(nums.begin(), nums.end());

    int size = 1, last = nums[0];
    for(int num : nums) {
        if (last != num) {
            last = num;
            size = res.size();
        }

        int newSize = res.size();
        for (int i=newSize-size; i<newSize; i++) {
            res.push_back(res[i]);
            res.back().push_back(num);
        }
    }

    return res;
}

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

子问题就是  下一次函数的调用应该是已经生成subset
比如集合[1, 2, 3] 比如当前已经生成集合[[ ], [1]] 在调用递归函数 因该把剩下的元素的幂集合全部找到了
*/
void dfs(vector<int>& nums, int index, vector<int>& path, vector<vector<int>>& res) {
    res.push_back(path);
    for (unsigned int i = index; i < nums.size(); i++) {
        path.push_back(nums[i]);
        dfs(nums, i+1, path, res);
        path.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    if(nums.empty()) return {}; // 空集直接返回
    vector<vector<int>> res;
    printVector(res);
    cout << '\n';
    vector<int> path;
    std::sort(nums.begin(), nums.end());
    dfs(nums, 0, path, res);
    return res;
}

int main() {
    vector<int> v = {1, 2, 2, 2};
    vector<int> emp = {};
    auto tmp = subsets_iteration_dup(emp);
    printVector(tmp);

    cout << "------\n";
    vector<int> v1 = {1, 2, 3};
    auto t = subsets(v1);
    printVector(t);
}