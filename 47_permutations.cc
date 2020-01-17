#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// https://zhuanlan.zhihu.com/p/41855459
// 排列 permutation 看重顺序
// 组合 combination 顺序无关


// https://www.cnblogs.com/grandyang/p/4359825.html
// 两次剪枝的作用不一样 但是易于理解
void permuteUniqueDFS(vector<int>& nums, int level, vector<int>& visited, vector<int>& out, vector<vector<int>>& res) {
    if (level >= nums.size()) {res.push_back(out); return;}
    for (int i = 0; i < nums.size(); ++i) {
        if (visited[i] == 1) continue;
        if (i > 0 && nums[i] == nums[i - 1] && visited[i - 1] == 0) continue;
        visited[i] = 1;
        out.push_back(nums[i]);
        permuteUniqueDFS(nums, level + 1, visited, out, res);
        out.pop_back();
        visited[i] = 0;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> out, visited(nums.size(), 0);
    // @TODO为什么需要排序  (如果数组是不重复的, 不需要排序)
    sort(nums.begin(), nums.end());
    permuteUniqueDFS(nums, 0, visited, out, res);
    return res;
}


// 用了一个set 基本上就直接区重 但是没有深入问题的本质
set<vector<int> > res;
void permutation(vector<int>& v, int start) {
	int n = v.size();
	if( (start+1) == n) {
        res.insert(v);
		// for(auto i : v) cout << i;
		// cout << endl;
	}
	else {
        // for循环i: [start, n-1]所以需要额外的数组记录是否重复)
        // invariant: num[0..start-1] have been fixed/permuted
        // start = 1表示前面两个数字已经固定
		for(int i=start; i<n; ++i) {
		    // if(v[start] == v[i+1]) continue;
			// else {
		    	swap(v[i], v[start]);
			    permutation(v, start+1);
			    swap(v[i], v[start]);
			// }
		}
	}
}

int main() {
	vector<int> a {1, 2, 2};
	permutation(a, 0);

    for(auto pa: res) {
        for (auto i: pa) {
            cout << i;
        }
        cout << endl;
    }
	// permutation(a, 1);
	// permutation(a, 2);
	// permutation(a, 3);

	return 0;
}
