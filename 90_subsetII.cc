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
        for (int i=newSize-size; i<newSize; i++) {  // 这个是遍历res的集合元素的大小
            res.push_back(res[i]);
            res.back().push_back(num);
        }
    }

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