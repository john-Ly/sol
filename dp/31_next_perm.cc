#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

// https://zhuanlan.zhihu.com/p/41855459
// 排列 permutation 看重顺序
// 组合 combination 顺序无关

/*
http://xiaohuiliucuriosity.blogspot.com/2014/12/permutations.html
https://leetcode.com/problems/permutations/discuss/18247/My-elegant-recursive-C%2B%2B-solution-with-inline-explanation

https://leetcode.com/problems/permutations/discuss/18360/C%2B%2B-backtracking-and-nextPermutation

https://leetcode.com/problems/permutations-ii/discuss/18669/C%2B%2B-backtracking-and-nextPermutation
----------------------------------------------------------

Basic idea: permutation of A[1..n] equals to
A[1] + permutation of (A[1..n] - A[1])
A[2] + permutation of (A[1..n] - A[2])
...
A[n] + permutation of (A[1..n] - A[n]).
*/

namespace str_permutation {
void AllRange(string str, int start) {
	if(start == str.size()) {
        cout << str << endl;
        return;
	}

    for(int i=start; i<str.size(); i++) {
        std::swap(str[start], str[i]);
        AllRange(str, start+1);
        std::swap(str[start], str[i]);
    }
}

void Permutation(string& str) {
	if(str.size() == 0)	return;
	AllRange(str, 0);
}

}

namespace best {

vector<vector<int> > permute(vector<int> &num) {
    // 因为有重复的存在 需要先排序
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    permuteRecursive(num, 0, res);
    // permuteRecursive_sort(num, 0, res);
    return res;
}

// permute num[begin..end]
// invariant: num[0..begin-1] have been fixed/permuted
// 先产生 0,1,2...,n-1
//     返回的时候需要swap back
//        0 1 2 , n-1, n-2
//
// num 应该传值 否则会出现干扰
void permuteRecursive(vector<int> num, int begin, vector<vector<int> > &result)	{
    if (begin >= num.size()) {
        result.push_back(num);
        return;
    }

    for (int i = begin; i < num.size(); i++) {
        swap(num[begin], num[i]);
        permuteRecursive(num, begin + 1, result);
        swap(num[begin], num[i]);
    }
}

void permuteRecursive_sort(vector<int> num, int begin, vector<vector<int> > &result)	{
    if (begin >= num.size()) {
        result.push_back(num);
        return;
    }

    for (int i = begin; i < num.size(); i++) {
        if (i == begin || num[i] != num[begin]) {
            swap(num[begin], num[i]);
            permuteRecursive_sort(num, begin + 1, result);
            // 因为重复的存在 进入判断后 不要回溯(之前的都是重复)
            // swap(num[begin], num[i]);
        }
    }
}
}

namespace permutation {
// https://www.cnblogs.com/grandyang/p/4428207.html
// https://leetcode.com/problems/next-permutation/solution/
// 动画演示
/*
1 　*2*　　7　　4　　3   1    逆序: 找到第一个不按照升序的数字 pivote
1 　*2*　　7　　4   *3*  1    逆序: 找到第一个 大于pivote的数字下标
1 　*3*　　7　　4   *2*  1    交换下标 i, j
1 　 3    *1　　2    4   7*
*/

// orig: 1 2 7 4 3 1
// prev: 1 2 7 4 1 3
// next: 1 3 1 2 4 7

// 默认n 是1-9的范围 全排列也就9!
string getPermutation(int n, int k) {
    // 循环使用next_permutaion

}

//  1 2 3  next_perm -> true
//  3 2 1  next_perm -> false 没有可以在排列的序列
void nextPermutation(vector<int>& nums) {
    bool rv = false;
    int n = nums.size(), i = n - 2, j = n - 1;
    while (i >= 0 && nums[i] >= nums[i + 1]) --i;
    if (i >= 0) {
        while (nums[j] <= nums[i]) --j;
        swap(nums[i], nums[j]);
        rv = true;
    }
    reverse(nums.begin() + i + 1, nums.end());
    return rv;
}


// @TODO prev 实际上不是相反的逻辑 很难写正确
void prePermutation(vector<int>& nums) {
    int n = nums.size(), i = 0, j = 1;
    while (j < n && nums[j] >= nums[j-1]) ++j;
    if (j < n) {
        while (nums[j] >= nums[i]) ++i;
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + j + 1, nums.end());
}
}

// 有重复存在 (终极方案)
// std::next_permutation 从升序开始 循环后返回false
vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> perms;
    do {
        perms.push_back(nums);
    } while(std::next_permutation(nums.begin(), nums.end()));
    return perms;
}

namespace deprecated {
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

	// vector<int> a {1, 2, 2};
	// permutation(a, 0);
}

int main(int argc, char *argv[]) {
    vector<int> v {1, 2, 7, 4, 3, 1};
    nextPermutation(v);
    nextPermutation(v);
    std::copy(v.begin(), v.end(),
            std::ostream_iterator<int>(cout, ","));
    cout << endl;
    return 0;
}
