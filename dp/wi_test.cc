#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool helper(string& S, int s, string& W, int w, vector<vector<int>>& cache) {
    int& ret = cache[w][s];
    if(ret != -1) return ret;

    while(s<S.size() && w<W.size() &&
        (W[w] == '?' || W[w] == S[s])) {
        return ret = helper(S, s+1, W, w+1, cache);
    }

    // 已达到范式最后一个字符 字符串也到最后一个字符 匹配
    if(w == W.size())
        return ret = (s == S.size());

    // 遇到 * 结束循环 --- 利用递归调用 查看 * 对应多少个字符
    if(W[w] == '*')
        // * 不匹配当前字符          匹配剩余的字符
        if( helper(S, s, W, w+1, cache) || (s<S.size() && helper(S, s+1, W, w, cache)) )
            return ret = 1;

    // 除此之外所有关系不成立
    return ret = 0;
}

bool isMatch(string s, string p) {
    vector<vector<int>> cache(p.size()+1, vector<int>(p.size()+1, -1));
    return helper(s, 0, p, 0, cache);
}

int main(int argc, char *argv[])
{
    string s = "aa", p = "*";
    cout << isMatch(s, p) << endl;
    return 0;
}
