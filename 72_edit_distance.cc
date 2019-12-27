#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/edit-distance/discuss/25846/C%2B%2B-O(n)-space-DP
// 2D -> 1D @TODO


// https://leetcode.com/problems/edit-distance/discuss/25849/Java-DP-solution-O(nm)  解释清晰
// 要求f(i,j) 假定插入 删除和替换后 f(.., ..) 都是match的 然后选出最小的
// https://leetcode.com/problems/edit-distance/discuss/25849/Java-DP-solution-O(nm)
// f(i, j) := minimum cost (or steps) required to convert first i characters of word1 to first j characters of word2
//         s1.substr(0,i) 左闭右开 前i个字符 [0,i-1]

// 思路还是倒推 从最后一个字符串开始
// Case 1: word1[i] == word2[j], i.e. the ith the jth character matches.
//    f(i, j) = f(i - 1, j - 1)

// Case 2: word1[i] != word2[j], then we must either insert, delete or replace, whichever is cheaper
//    f(i, j) = 1 + min { f(i, j - 1), f(i - 1, j), f(i - 1, j - 1) }
//    f(i, j - 1) represents insert operation
//    f(i - 1, j) represents delete operation
//    f(i - 1, j - 1) represents replace operation

// Here, we consider any operation from word1 to word2. It means, when we say insert operation, we insert a new character after word1 that matches the jth character of word2. So, now have to match i characters of word1 to j - 1 characters of word2. Same goes for other 2 operations as well.
// 插入操作: 说明需要对 s1[0, i]  s2[0, j-1]进行match操作
namespace so1 {
int match(string s1, string s2, int i, int j) {
    // cout << s1.substr(0, i) << "--" << s2.substr(0, j) << endl;
    //If one of the string's pointer have reached the end of it
    if (s1.size() == i) {
        return s2.size() - j; // 左闭右开的优势
        // 二分查找有几种写法？它们的区别是什么？ - Jason Li的回答 - 知乎
        // https://www.zhihu.com/question/36132386/answer/530313852
    }
    if (s2.size() == j) {
        return s1.size() - i;
    }

    int res;
    //If current poisition is the same.
    if (s1[i] == s2[j]) {
        res = match(s1, s2, i + 1, j + 1);
    } else {
        //Case1: insert
        int insert = match(s1, s2, i, j + 1);
        //Case2: delete
        int remove = match(s1, s2, i + 1, j);
        //Case3: replace
        int replace = match(s1, s2, i + 1, j + 1);
        res = min(min(insert, remove), replace) + 1;
    }

    return res;
}
int minDistance(string word1, string word2) {
    if (word1.size() == 0) return word2.size();
    if (word2.size() == 0) return word1.size();

    return match(word1, word2, 0, 0);
}

}

// 实际运行效率很低
// @TODO 动规 采用返回dp[0][0]的思路
// https://leetcode.com/problems/edit-distance/discuss/25895/Step-by-step-explanation-of-how-to-optimize-the-solution-from-simple-recursion-to-DP
namespace so2 {
int match(string s1, string s2, int i, int j, vector<vector<int>>& v) {
    // cout << s1.substr(0, i) << "--" << s2.substr(0, j) << endl;
    //If one of the string's pointer have reached the end of it
    int& ret = v[i][j];
    if (s1.size() == i) {
        return ret = s2.size() - j; // 左闭右开的优势
    }
    if (s2.size() == j) {
        return ret = s1.size() - i;
    }

    if(ret != -1) return ret;
    // res = 0;
    //If current poisition is the same.
    if (s1[i] == s2[j]) {
        ret = match(s1, s2, i + 1, j + 1, v);
    } else {
        //Case1: insert
        int insert = match(s1, s2, i, j + 1, v);
        //Case2: delete
        int remove = match(s1, s2, i + 1, j, v);
        //Case3: replace
        int replace = match(s1, s2, i + 1, j + 1, v);
        ret = min(min(insert, remove), replace) + 1;
    }

    return ret;
}

int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    if (m == 0) return n;
    if (n == 0) return m;

    vector<vector<int>> cache(m+1, vector<int>(n+1, -1));
    return match(word1, word2, 0, 0, cache);
}

// 迭代采用 从00开始比递归的思路要好
namespace so3 {
int minDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    if (m == 0) return n;
    if (n == 0) return m;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) { dp[i][0] = i; }
    for (int j = 1; j <= n; j++) { dp[0][j] = j; }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }
    }
    return dp[m][n];
}
}

}
int main() {
    string s1 = "horse";
    string s2 = "ros";
    cout << so1::minDistance(s1, s2) << endl;
    cout << so2::minDistance(s1, s2) << endl;

    return 0;
}