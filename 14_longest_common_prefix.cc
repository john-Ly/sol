#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    sort(strs.begin(), strs.end());
    int i = 0, len = min(strs[0].size(), strs.back().size());
    while (i < len && strs[0][i] == strs.back()[i]) ++i;
    return strs[0].substr(0, i);
}

int main() {
    vector<string> v = {"flower","flow","flight"};
    vector<string> v1 = {"dog","racecar","car"};
    cout << longestCommonPrefix(v) << endl;
    cout << longestCommonPrefix(v1) << endl;
    return 0;
}