#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// @SEE code/STRING/suffixArray.cpp 字典序 与 全排列的关系
// 后缀数组
// http://dongxicheng.org/structure/permutation-combination/
// http://dongxicheng.org/structure/structure-algorithm-summary/
// @SEE subset

// https://www.cnblogs.com/grandyang/p/4358848.html
// http://forum.codecall.net/topic/64715-how-to-generate-all-permutations/

// @SEE subsetII.cc
// @TODO 未理解
// 问题是 perm(v, start) =
// fixed-head solution

// start表示:  为全排列开始数字的下标
// i表示:  表示从start开始到n的遍历

/*
http://xiaohuiliucuriosity.blogspot.com/2014/12/permutations.html

Basic idea: permutation of A[1..n] equals to
A[1] + permutation of (A[1..n] - A[1])
A[2] + permutation of (A[1..n] - A[2])
...
A[n] + permutation of (A[1..n] - A[n]).
*/

void permutation(vector<int>& v, int start) {
	int n = v.size();
	if( (start+1) == n) {
		for(auto i : v) cout << i;
		cout << endl;
	}
	else {
        // for循环i: [start, n-1]所以需要额外的数组记录是否重复)
        // invariant: num[0..start-1] have been fixed/permuted
        // start = 1表示前面两个数字已经固定
		for(int i=start; i<n; ++i) {
		    // if(v[start] == v[i+1]) continue;
			// else {
            // cout << "i=" << i << " start=" << start << endl;
		    	swap(v[i], v[start]);
			    permutation(v, start+1);
			    swap(v[i], v[start]);
			//}
		}
	}
}

/*
i=0 start=0
i=1 start=1
012
i=2 start=1
021
i=1 start=0
i=1 start=1
102
i=2 start=1
120
i=2 start=0
i=1 start=1
210
i=2 start=1
201

 */

// visited()记录是否遇到过该数字
// for循环i开始的值不同  (i: [0, n-1]所以需要额外的数组记录是否重复)
void permuteDFS(vector<int>& num, int level, vector<int>& visited, vector<int>& out, vector<vector<int>>& res) {
    if (level == num.size()) {res.push_back(out); return;}
    for (int i = 0; i < num.size(); ++i) {
        if (visited[i] == 1) continue;
        visited[i] = 1;
        out.push_back(num[i]);
        permuteDFS(num, level + 1, visited, out, res);
        out.pop_back();
        visited[i] = 0;
    }
}

vector<vector<int>> permute(vector<int>& num) {
    vector<vector<int>> res;
    vector<int> out, visited(num.size(), 0);
    permuteDFS(num, 0, visited, out, res);
    return res;
}

vector<vector<int>> permute2(vector<int>& num) {
    vector<vector<int>> res;
    sort(num.begin(), num.end());
    res.push_back(num);
    while (next_permutation(num.begin(), num.end())) {
        res.push_back(num);
    }
    return res;
}


int main() {
	vector<int> a {0, 1, 2, 2};
	permutation(a, 0);
	// permutation(a, 1);
	// permutation(a, 2);
	// permutation(a, 3);

	return 0;
}
