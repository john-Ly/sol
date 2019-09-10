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

void DFS(vector<int>& candidates, int target, int smallest, vector<int>& out, vector<vector<int>>& res) {
    if (target == 0) {res.push_back(out); return;}

    // 可以重复选择  8= 2+2+2+2 所以这种方式行不通 第三次递归调用size出现问题
	// int smallest = out.empty() ? 0 : out.size()-1;
    // 如果直接设置i=0, 会导致重复组合( [3,5]和[5,3] )
    for(int i=smallest; i<candidates.size() && target >= candidates[i]; ++i) {
        out.push_back(candidates[i]);
        DFS(candidates, target - candidates[i], i, out, res);
        out.pop_back();
    }
}

void DFS1(vector<int>& candidates, int target, vector<int>& out, vector<vector<int>>& res) {
    if (target == 0) {res.push_back(out); return;}

    // https://leetcode.com/problems/combination-sum-iv/
    // 如果直接设置i=0, 会导致重复组合( [3,5]和[5,3] )
    for(int i=0; i<candidates.size() && target >= candidates[i]; ++i) {
        out.push_back(candidates[i]);
        DFS1(candidates, target - candidates[i], out, res);
        out.pop_back();
    }
}

// https://www.cnblogs.com/grandyang/p/4419259.html
auto combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> out;
    // 排序为了按照顺序选取
    std::sort(candidates.begin(), candidates.end());
    // DFS(candidates, target, 0, out, res);
    DFS1(candidates, target, out, res);
    return res;
}

int main() {
    vector<int> v = {1, 2, 3};
    int t = 4;
    auto tmp = combinationSum(v, t);
    printVector(tmp);

    return 0;
}