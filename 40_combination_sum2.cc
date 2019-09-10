#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4419386.html
// https://leetcode.com/problems/combination-sum/discuss/16496/Accepted-16ms-c%2B%2B-solution-use-backtracking-easy-understand.

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

// https://leetcode.com/problems/combination-sum-ii/discuss/16861/Java-solution-using-dfs-easy-understand/16645
// That is to skip the duplicate number, for you may have just traveled a path using it. See the number 1 in case of [1, 1, 2, 5, 6, 7 10 ]
// 这一题限制进制使用重复 应该是递归调用是不同层次出现(所以必须sort把相同的数字聚簇)
void DFS(vector<int>& candidates, int target, int smallest, vector<int>& out, vector<vector<int>>& res) {
    if (target == 0) {res.push_back(out); return;}

    // 可以重复选择  8= 2+2+2+2 所以这种方式行不通 第三次递归调用size出现问题
	// int smallest = out.empty() ? 0 : out.size()-1;
    // 如果直接设置i=0, 会导致重复组合( [3,5]和[5,3] )
    for(int i=smallest; i<candidates.size() && target >= candidates[i]; ++i) {
        if (i > start && candidates[i] == candidates[i - 1]) continue;
        out.push_back(candidates[i]);
        DFS(candidates, target - candidates[i], i+1, out, res);
        out.pop_back();
    }
}

auto combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> out;
    // 排序为了按照顺序选取
    std::sort(candidates.begin(), candidates.end());
    DFS(candidates, target, 0, out, res);
    return res;
}

int main() {
    vector<int> v = {2, 3, 5};
    int t = 8;
    auto tmp = combinationSum(v, t);
    printVector(tmp);

    return 0;
}