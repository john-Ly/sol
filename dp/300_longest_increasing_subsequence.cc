#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>     // memset()
#include <functional>  // std::swap
#include <limits>
using namespace std;
// lis: 严格的递增序列  (子串要求连续 子序列不要求)

namespace book {
vector<int> a { 10, 22, 9, 33, 21, 50, 41, 60 };
vector<int> b { 5, 2, 1, 4, 5, 4, 5, 3, 6};
const long long NEGINF = numeric_limits<long long>::min();

// 假设已知dp[i] 求出 dp[i+1...]
// 书上的思路和leetcode思路不一样 主要是使用递归习惯了
// 相当于遍历所有的可能
// for (ele : v):
//    for (ele+1 : v):
//        挑选出之后大于ele的序列v`
//    求出 res = max(res, 1+lis(v`))
int lis(const vector<int>& A) {
	if(A.empty()) return 0;
	int ret = 0;
	for(int i=0; i<A.size(); ++i) {
		vector<int> B;
		for(int j=i+1; j<A.size(); ++j)
		    if(A[i]<A[j]) B.push_back(A[j]);
        // 序列B包含所有大于 A[i]的数字, 也就是下一个可能的lis

        auto tmp = 1+lis(B);
		ret = max(ret, tmp);
	}
	return ret;
}

// 需要单独指定起始值
// cache[i] = 表示字符串S[i...]里面的lis
int lis2(int start) {
	int& ret = cache[start];
	if(ret != -1) return ret;

    // 总是存在S[start] 故长度至少为1
	ret = 1;
	for(int next=start+1; next<a.size(); ++next) {
	    if(a[start]<a[next]) {
	        auto tmp = 1+lis2(next);
	        ret = max(ret, tmp);
        }
        // ret = max(ret, 1+lis3(next));
	}
	return ret;
}

}

namespace dp_array {
// https://www.cnblogs.com/grandyang/p/4938187.html

// dp[i] = 表示从nums[0,i] 的lis值
// 从dp[i]前面的数据推出dp[i]
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1);
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        res = max(res, dp[i]);
    }
    return res;
}

// https://blog.csdn.net/wbin233/article/details/77570070
// 利用贪心的思想，对于一个上升子序列，显然当前最后一个元素越小，越有利于添加新的元素，这样LIS长度自然更长。
// https://zhuanlan.zhihu.com/p/47096098

int lengthOfLIS_3(vector<int>& nums) {
    vector<int> v;
    for (auto a : nums) {
        auto it = lower_bound(v.begin(), v.end(), a);
        if (it == v.end()) v.push_back(a);
        else *it = a;
    }
    return v.size();
}

int lengthOfLIS_2(vector<int>& nums) {
    vector<int> dp;
    for (int i = 0; i < nums.size(); ++i) {
        //////////////
        int left = 0, right = dp.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (dp[mid] < nums[i]) left = mid + 1;
            else right = mid;
        }
        //////////////  找到lower_bound
        if (right >= dp.size()) dp.push_back(nums[i]);
        else dp[right] = nums[i];
    }
    return dp.size();
}
}