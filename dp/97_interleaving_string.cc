#include <iostream>
#include <unordered_set>
#include <string>
#include <queue>
using namespace std;


// https://www.cnblogs.com/grandyang/p/4298664.html
// DP + 搜索的方式(BFS/DFS) + 递归/递推
// https://leetcode.com/problems/interleaving-string/discuss/31904/Summary-of-solutions-BFS-DFS-DP

// https://leetcode.com/problems/interleaving-string/discuss/31879/My-DP-solution-in-C%2B%2B
// DP思路
// dp[i][j] = s1的前i个字符 和 s2的前j 个字符  是否是interleaving的方式  生成了s3 前i+j个 (前j个 包含j)
bool isInterleave_dp(string s1, string s2, string s3) {
    // 1. 长度保证
    if(s3.length() != s1.length() + s2.length())
        return false;

    bool table[s1.length()+1][s2.length()+1];

    // 相当于遍历这张表(因为树 图 都可以写成二维矩阵的形式)
    for(int i=0; i<s1.length()+1; i++)
        for(int j=0; j< s2.length()+1; j++){
            if(i==0 && j==0) // 空串
                table[i][j] = true;
            else if(i == 0)  //  其中一个为空串, 另一个字符串一定要和s3每个字符匹配才正确
                table[i][j] = ( table[i][j-1] && s2[j-1] == s3[i+j-1]);
            else if(j == 0)
                // s2 最多有j个字符, 因此下标j-1   所以s3也是j-1
                table[i][j] = ( table[i-1][j] && s1[i-1] == s3[i+j-1]);
            else
            // table[][] 左边和右边的只要有一个true就会 判断
                table[i][j] = (table[i-1][j] && s1[i-1] == s3[i+j-1] ) || (table[i][j-1] && s2[j-1] == s3[i+j-1] );
        }
    return table[s1.length()][s2.length()];
}


// BFS
// 1. 如何定义二维座标定义key(@TODO)
// https://leetcode.com/problems/interleaving-string/discuss/31948/8ms-C%2B%2B-solution-using-BFS-with-explanation
// 2.
struct MyPoint {
    int x, y;
    bool operator==(const MyPoint &p) const { return p.y == y && p.x == x; }
};

namespace std {
// 1. 如何自定义hash 值
template <>
struct hash<MyPoint> {
    size_t operator () (const MyPoint &f) const {
        return (std::hash<int>()(f.x) << 1) ^ std::hash<int>()(f.y);
    }
};
}

// https://leetcode.com/problems/interleaving-string/discuss/31948/8ms-C++-solution-using-BFS-with-explanation/276068
// @TODO 运算错误 但是思路正确
bool isInterleave_bfs(string s1, string s2, string s3) {
    if (s1.size() + s2.size() != s3.size()) return false;
    int n1 = s1.size(), n2 = s2.size(), n3 = s3.size(), k = 0;
    unordered_set<MyPoint> visited;
    queue<MyPoint> q;
    q.push({0, 0});
    while(!q.empty()) {
        auto p = q.front(); q.pop();
        // cout << p.x << '-' << p.y << '\n';
        if(p.x == n1 && p.y == n2) { return true; }
        if (visited.count(p) != 0) continue;

        if(p.x < n1 && s1[p.x] == s3[p.x + p.y]) { q.push({p.x+1, p.y}); }
        if(p.y < n2 && s2[p.y] == s3[p.x + p.y]) { q.push({p.x, p.y+1}); }
        visited.insert(p);
    }
    return false;
}

int main() {
    string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
    cout << isInterleave_bfs(s1, s2, s3) << endl;
    cout << isInterleave_dp(s1, s2, s3) << endl;
}
