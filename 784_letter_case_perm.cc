#include <iostream>
#include <vector>
#include <string>
using namespace std;

// https://www.cnblogs.com/grandyang/p/9065702.html
vector<string> letterCasePermutation(string S) {
    vector<string> res {""};
    for (char c : S) {
        int len = res.size();
        if (c >= '0' && c <= '9') {
            // 当前字符是数字: 要在res每一个字符串 push_back
            for (string &str : res)
                str.push_back(c);
        } else {
            // 当前字符是字母:
            // S = "abc"，那么先让 res = [""]，然后res中的每个字符串分别加上第一个字符a和A，得到 ["a", "A"]
            // 然后res中的每个字符串分别加上第二个字符b和B，得到 ["ab", "Ab", "aB", "AB"]
            // 然后res中的每个字符串分别加上第三个字符c和C，得到 ["abc", "Abc", "aBc", "ABc", "abC", "AbC", "aBC", "ABC"]
            for (int i = 0; i < len; ++i) {
                res.push_back(res[i]);
                // 分别处理大小写
                res[i].push_back(tolower(c));
                res[len + i].push_back(toupper(c));
            }
        }
    }
    return res;
}

int main() {
    string s = "a1b2";
    for(auto s: letterCasePermutation(s)) {
        cout << s << endl;
    }

    return 0;
}