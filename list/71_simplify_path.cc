#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// https://leetcode.com/problems/simplify-path/discuss/25680/C%2B%2B-10-lines-solution

string simplifyPath(string path) {
    string res, tmp;
    vector<string> stk;
    stringstream ss(path);
    int cnt = 0;
    while(getline(ss,tmp,'/')) {
        cnt++;
        if (tmp == "" or tmp == ".") continue;
        if (tmp != "..") stk.push_back(tmp);
        else if (/* tmp == ".." && */ !stk.empty()) stk.pop_back();
    }
    cout << cnt << endl;

    for(auto str : stk) res += "/"+str;
    return res.empty() ? "/" : res;
}

int main() {
    cout << simplifyPath("/home/") << endl;
    cout << "===" << endl;
    cout << simplifyPath("/../") << endl;
    cout << "===" << endl;
    cout << simplifyPath("/home//foo/") << endl;
    cout << "===" << endl;
    cout << simplifyPath("/a/./b/../../c/") << endl;
    cout << "===" << endl;
    cout << simplifyPath("/a/../../b/../c//.//") << endl;
    cout << "===" << endl;
    cout << simplifyPath("/a//b////c/d//././/..") << endl;
    cout << "===" << endl;

    return 0;
}