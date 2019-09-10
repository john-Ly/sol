// 同构字符串(每个字符都被映射到另外一个字符 且只能一一映射)
// http://www.cnblogs.com/grandyang/p/4465779.html
#include <iostream>
#include <string>

#include <cstring>
#include <cassert>
using namespace std;

bool isIsomorphic(string s, string t) {
    const size_t n = s.size();
    assert(n == t.size());

    // 相当于字典桶 每一个位置代表 对应的index
    char m1[256], m2[256];
    ::memset(m1, -1, sizeof(m1));
    ::memset(m2, -1, sizeof(m2));

    for ( int i=0; i < n; ++i) {
        if ( m1[s[i]] != m2[t[i]] )
            return false;

        m1[s[i]] = i;
        m2[t[i]] = i;
    }

    return true;
}

int main () {
    cout << isIsomorphic("aabcdet", "xxyopqm") << endl;
    cout << isIsomorphic("aab", "xyz") << endl;
    return 0;
}
