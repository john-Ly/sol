#include <unordered_set>
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;


// https://www.cnblogs.com/grandyang/p/4257740.html
// https://leetcode.com/problems/word-break/discuss/43808/Simple-DP-solution-in-Python-with-description
// dp
class Solution {
public:
// bool dp[i] = 表示 字符串s [0, i) 是否可以拆分
// 字符串 可以完全有wordDict中的word 表示
// leetcode = "leet" "code"
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true; // 要处理空字符串

    // dp.size = 9
    for (int i = 0; i < dp.size(); ++i) {
        // 在[0, i) 范围内  即s的前i个范围内, 字符串是否可以被字典中的word拼接
        // [0, j) + [j, i)
        for (int j = 0; j < i; ++j) {
            //  无后效性 可以直接dp[j] 作为第一个条件 所以可以利用之前的结果
            if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp.back();
}
};

// bfs
class Solution2 {
public:
bool wordBreak(string& s, vector<string>& wordDict) {
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    vector<bool> visited(s.size(), false);
    queue<int> Q;
    Q.push(0);

    while (!Q.empty()) {
        int start = Q.front();
        Q.pop();
        if (!visited[start]) {
            for (int i = start + 1; i <= s.size(); ++i) {
                if (wordSet.count(s.substr(start, i - start))) {
                    Q.push(i);
                    if (i == s.size()) return true;
                }
            }
            visited[start] = true;
        }
    }

    return false;
}
};


// dfs+memo
class Solution3 {
public:
// bool dp[i] = 表示 字符串s [0, i) 是否可以拆分
// 字符串 可以完全有wordDict中的word 表示
// leetcode = "leet" "code"
bool wordBreak(string& s, vector<string>& wordDict) {
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    vector<int> memo(s.size(), -1);
    return check(s, wordSet, 0, memo);
}

bool check(string s, unordered_set<string>& wordSet, int start, vector<int>& memo) {
    if (start >= s.size()) return true;
    if (memo[start] != -1) return memo[start];
    //                      i 要计算个数 substr
    // substr(start, cnt) cnt表示字符的个数
    for (int i = start + 1; i <= s.size(); ++i) {
        if (wordSet.count(s.substr(start, i - start)) && check(s, wordSet, i, memo)) {
            return memo[start] = 1;
        }
    }
    return memo[start] = 0;
}
};

// word break 2
class Solution4 {
public:
vector<string> wordBreak(string s, vector<string>& wordDict) {
    unordered_map<string, vector<string> > word_map;
    return check(s, wordDict, word_map);
}

vector<string> check(string s, vector<string>& wordDict, unordered_map<string, vector<string> >& word_map) {
    if (s.empty()) return {""};
    if (word_map.count(s)) return word_map[s];

    vector<string> res;
    for (auto& word : wordDict) {
        if (s.substr(0, word.size()) != word) continue;
        vector<string> rest = check(s.substr(word.size()), wordDict, word_map);
        for (auto& str : rest) {
            res.push_back(word + (str.empty() ? "" : " ") + str);
        }
    }

    word_map[s] = std::move(res);
    return word_map[s];
}

};


int main() {
    vector<string> wordDict = {"leet", "code"};
    string s = "leetcode";
    Solution sol;
    cout << sol.wordBreak(s, wordDict) << '\n';

    {
        string s = "catsanddog";
        vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};
        Solution4 sol4;
        vector<string> res = sol4.wordBreak(s, wordDict);
        std::copy(res.begin(), res.end(), ostream_iterator<string>(cout, "\n"));
    }

    return 0;
}