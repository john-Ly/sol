#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
*/

namespace jump1 {
// 但是DP的思路还没有向清楚  @TODO
// 下面链接有一个关于DP和贪心的图
// https://leetcode.com/problems/jump-game/discuss/20917/Linear-and-simple-solution-in-C++/187269
// @TODO 贪心的思想还是不太理解
bool canJump(vector<int>& nums) {
    int n = nums.size(), reach = 0;
    for (int i = 0; i < n; ++i) {
        // i>reach: reach是上一次更新后的, reach只能到达i前面的位置, 说明reach到达不了终点
        if (i > reach || reach >= n - 1) break;
        // if (i > reach) return false;
        //                 i+nums[i]表示当前位置i能到达最远的位置
        reach = max(reach, i + nums[i]);
    }
    return reach >= n - 1;

// dp[i] 到达i下标位置的时候, 还剩下多少步跳力 (0: 表示刚好能跳到目标位置; >0 还有剩余跳力; <0 不能跳到)
// dp[i] = max(dp[i-1], nums[i-1]) - 1;
// 因为是从上一个下标 i-1 来跳到 i, 所以最后要减一
// https://www.cnblogs.com/grandyang/p/4371526.html
bool canJump_dp(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 0);
    // 因为采用for循环 肯定能够遍历到最后一个位置(@TODO 一个优化的点就是 不要一次一个的遍历计算)
    for (int i = 1; i < n; ++i) {
        dp[i] = max(dp[i-1], numsp[i-1]) - 1;
        if (dp[i] < 0) return false;
    }

    for(auto i: dp) cout << i << " ";
    cout << endl;
    return true;
}

// @SEE P150 上面棋盘的数字是比需要跳的步数, 而leetcode的题目则是 表示跳力(最多可以跳多少)
int n , board[100][100];
int cache[100][100];
int canJump2(int y, int x) {
    int& ret = cache[y][x];
    if(y >= n || x >= n) return ret = 0;
    if(y == n-1 && x == n-1) return ret = 1;

    // 制表
    if(ret != -1) reuturn ret;
    int jumpSize = board[y][x];
    return ret = (canJump2(y+jumpSize, x) || canJump2(y, x+jumpSize));
}
}

namespace jump2 {
// 实际上是 BFS的演化(画出每个节点的图关系  [0, n-1] )
// http://www.allenlipeng47.com/blog/index.php/2016/09/12/jump-game-ii/
// https://leetcode.com/problems/jump-game-ii/discuss/18014/Concise-O(n)-one-loop-JAVA-solution-based-on-Greedy
int jump(vector<int>& nums) {
	int jumps = 0, curEnd = 0, curFarthest = 0;
    // 因为起点是0, 终点是n-1, 所以遍历到n-2即可
	for (int i = 0; i < A.size()-1; i++) {
		curFarthest = max(curFarthest, i + A[i]);
        // the current point reaches curEnd, then trigger another jump
		if (i == curEnd) {
			jumps++;
			curEnd = curFarthest;
		}
	}
	return jumps;
}
}

int main() {
    vector<int> v {2,3,1,1,4};
    cout << jump1::canJump(v) << endl;
    return 0;
}