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

// 最优问题: 可以使用dp数组  === 求一个数
// 背包问题: 最大收益  @SEE packing.cc
// coin_change: 最少的硬币凑零钱
//
// 所有组合: 常用dfs  === vector<vector<>> 所有情况 或者是一个数
// combination_sum:
// 1.  sum = 所有数字组合(数字可以重复使用) 但是重复的不要 求组合
// 2.

// 注意点:
//  调用之前要排序(如果是需要组合数)
//  dfs(int start, vector<int> out, vector<vector<int>> res)
// 1. start: 表示 [0, start-1] 都已经计算了 -> 本次调用计算start -> 下次调用计算start+1
// 2. out 表示一次dfs搜索的结果   传值还是传引用
//    传值一定是对的
//        out.push_back(start)  传引用即可
//        swap(vec[i], vec[start])  需要传值 否则结果不正确

namespace combination_sum_vector {
// **完全背包**
// 原数组不重复 + 数字可以重复使用 + 只要组合(1,2) 和(2,1) 同一种
// https://www.cnblogs.com/grandyang/p/4419259.html
auto combinationSum_inf(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> out;
    // 排序 为了获取组合( [1,2], [2,1] 相同的组合 )
    std::sort(candidates.begin(), candidates.end());
    DFS(candidates, target, 0, out, res);
    // DFS_perm(candidates, target, out, res);
    return res;
}

// @NOTE start + sort 是求出组合而不是排列
void DFS(vector<int>& candidates, int target, int start, vector<int>& out, vector<vector<int>>& res) {
    if (target == 0) {res.push_back(out); return;}

    // @NOTE 如果直接设置i=0, 会导致重复组合( [3,5]和[5,3] )
    for(int i=smallest; i<candidates.size() && target >= candidates[i]; ++i) {
        out.push_back(candidates[i]);
        // 为什么还是i 而不是i+1
        // 因为可以重复选择 所以要dfs 取完所有
        DFS(candidates, target-candidates[i], i, out, res);
        out.pop_back();
    }
}

// 不重复 + 数字可以重复使用 + 组合(1,2) 和(2,1) 算两种
void DFS_perm(vector<int>& candidates, int target, vector<int>& out, vector<vector<int>>& res) {
    if (target == 0) {res.push_back(out); return;}

    // https://leetcode.com/problems/combination-sum-iv/
    // 直接设置i=0, 重复组合算两种情况( [3,5]和[5,3] )
    for(int i=0; i<candidates.size() && target>=candidates[i]; ++i) {
        out.push_back(candidates[i]);
        DFS_perm(candidates, target - candidates[i], out, res);
        out.pop_back();
    }
}

///////////////////////////////////////////////////////////////////
// 原数组重复 + 数字可以重复使用 + 只要组合(1,2) 和(2,1) 同一种
// https://www.cnblogs.com/grandyang/p/4419386.html
// https://leetcode.com/problems/combination-sum/discuss/16496/Accepted-16ms-c%2B%2B-solution-use-backtracking-easy-understand.
// https://leetcode.com/problems/combination-sum-ii/discuss/16861/Java-solution-using-dfs-easy-understand/16645
// That is to skip the duplicate number, for you may have just traveled a path using it. See the number 1 in case of [1, 1, 2, 5, 6, 7 10 ]

auto combinationSum_01(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> out;
    // 排序 为了获取组合( [1,2], [2,1] 相同的组合 )
    std::sort(candidates.begin(), candidates.end());
    DFS(candidates, target, 0, out, res);
    return res;
}

// @NOTE start + sort 是求出组合而不是排列
void DFS(vector<int>& candidates, int target, int start, vector<int>& out, vector<vector<int>>& res) {
    if (target == 0) {res.push_back(out); return;}

    // @NOTE 如果直接设置i=0, 会导致重复组合( [3,5]和[5,3] )
    for(int i=smallest; i<candidates.size() && target >= candidates[i]; ++i) {
        // @NOTE 原数组有重复 怎么去除 (1,1) (1,1)
        // 排序后 相同数字在一起, 所以第一次就可以 后面的情况跳过
        if (i > start && candidates[i] == candidates[i - 1]) continue;
        out.push_back(candidates[i]);
        // i+1 因为不能重复选择 当前元素
        DFS(candidates, target-candidates[i], i+1, out, res);
        out.pop_back();
    }
}

////////////////////////////////////////////////////////////////////
// **0-1背包**
// https://www.cnblogs.com/grandyang/p/4537983.html
// 求组合 相似             ---> 不是排列 无重复组合
// 数字范围限定在1-9       ---> 排序
// 每个元素只能挑选出 1次
// 从m个数 选出n个
void pick(int target, int toPick,
          vector<int>& picked, vector<vector<int> >& res) {
 	if(toPick == 0 && target==0) {
        res.push_back(picked);
		return;
 	}

    // 从1开始计数 (组合不能包含重复的项+按顺序生成)
	int smallest = picked.empty() ? 1 : picked.back() + 1;
	for(int next=smallest; next<=9; ++next){
		picked.push_back(next);
		pick(target-next, toPick-1, picked, res);
		picked.pop_back();
	}
}

vector<vector<int> > combinationSum3(int k, int n) {
    vector<vector<int> > res;
    vector<int> out;
    pick(n, k, out, res);
    return res;
}

}

// combination m from n.  组合数
namespace combination_math {
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
        pick(n, picked, toPick-1, res);
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
    //  1, 1, 1, ..., 0 0 0
    //  - m个1-                  进行排列permutation
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

// 求组合个数
namespace combination_sum_dp {
// 如果递归求出所有解的可能 会严重超时
// dp[i] 表示目标数为i的解的个数  dp[4] 表示目标为4 有多少种解
// dp[4] = (1+dp[3]) + (2+dp[2]) + (3+dp[1]) + (4+dp[0])
// https://www.cnblogs.com/grandyang/p/5705750.html
int combinationSum4(vector<int>& nums, int target) {
    vector<int> dp(target + 1);
    dp[0] = 1;
    // 排序是为了 先把小的排完
    sort(nums.begin(), nums.end());

    for (int i = 1; i <= target; ++i) {
        for (auto a : nums) {
            // i < a 说明后面的数都不用在遍历了
            if (i < a) break;
            dp[i] += dp[i-a];
        }
    }

    return dp.back();
}
}

// 求最优问题
namespace coin_change {
// https://www.cnblogs.com/grandyang/p/5138186.html
// 使用最少的硬币 来组成 amount(每种面额的硬币无限)

// 把所有amount的子问题全部计算出来  bottom_up
// dp[i] = 凑成i总数 需要最少硬币的个数
// dp(amount) = min(dp(amount), dp(amount-coinsp[i]) + 1)
// 一块硬币 选和不选+ 选几个

// @NOTE 没有排序 但是dp相当于把所有的可能都算出来更新到dp数组  -- 一个优化点 先从贪心(选面值尽可能大的硬币)
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    // 处理初始情况 后面想到
    dp[0] = 0;

    // 如果面值超过了i 直接break 避免太多循环
    sort(coins.rbegin(), coins.rend());
    for (int i = 1; i <= amount; ++i) {
        // dp[12] = min（ dp[11] + （1 这一枚硬币），dp[10] +（ 2 这一枚硬币），dp[7] + （5 这一枚硬币）)
        for (auto coin : coins) {
            if (coin > i) break;
            dp[i] = min(dp[i], dp[i-coin]+1);
        }
    }

    // 看测试用例
    // Input: coins = [2], amount = 3
    // Output: -1
    return (dp[amount] > amount) ? -1 : dp[amount];
}

// 重复子问题很严重
int process1(vector<int>& coins, int index, int amount) {
    int res = 0;
    if (index == coins.size()) {
        res = (amount == 0 ? 1 : 0);
    } else {
        for (int i=0; coins[index]*i <= amount; ++i) {
            res += process1(coins, index+1, amount-coins[index]*i);
        }
    }
}

int coinChange_recur(vector<int>& coins, int amount) {
    if (coins.empty() || amount <= 0) return 0;
    return process1(coins, 0, amount);
}

}

int main() {
    vector<int> v = {1, 2, 3};
    int t = 4;
    auto tmp = combinationSum(v, t);
    printVector(tmp);

    return 0;
}