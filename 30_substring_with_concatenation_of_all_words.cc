#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4521224.html
// 题目要求所有words中的字符串 串联连接 是否出现在S中, 有则返回相应的起始位置
// time: O(n * num)
vector<int> findSubstring(string s, vector<string>& words) {
    if (s.empty() || words.empty()) return {};
    vector<int> res;
    int n = words.size(), len = words[0].size();
    unordered_map<string, int> wordCnt;
    // 统计 words数组里面 word的个数 (如果用hash_set会丢失个数信息)
    for (auto &word : words) ++wordCnt[word];

    // 一定要将 s.size() 先转为整型数 @NOTE
    // size() 的返回是无符号型 如果做减法 需要强制转型(int)
    for (int i = 0; i <= (int)s.size() - n * len; ++i) {
        unordered_map<string, int> strCnt;
        int j = 0;
        for (j = 0; j < n; ++j) {
            // 每次取长度为len的子串, 看words是否包含
            // substr() linear_in_count
            string t = s.substr(i + j * len, len);

            if (!wordCnt.count(t)) break;
            ++strCnt[t];
            if (strCnt[t] > wordCnt[t]) break;
        }
        if (j == n) res.push_back(i);
    }
    return res;

}

int main() {
    // string s = "wordgoodgoodgoodbestword";
    // vector<string> words = {"word","good","best","word"};
    string s = "barfoothefoobarman";
    vector<string> words = {"foo","bar"};

    auto tmp = findSubstring(s, words);
    cout << "[";
    for (auto i: tmp)
        cout << i << " ";
    cout << "]";
    cout << endl;

    return 0;
}