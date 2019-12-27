// https://leetcode.com/problems/excel-sheet-column-number/discuss/52107/My-solutions-in-3-languages-does-any-one-have-one-line-solution-in-Java-or-C%2B%2B
int titleToNumber(string s) {
    int res = 0;
    for (auto c : s) {
    res = res*26 + (c-'A'+1);
    }
    return res;
}

// return n == 0 ? "" : convertToTitle(n / 26) + (char) (--n % 26 + 'A');
// https://leetcode.com/problems/excel-sheet-column-title/discuss/51398/My-1-lines-code-in-Java-C%2B%2B-and-Python
string convertToTitle(int n) {
    string res = "";
    while(n) {
    // --n  corner_case: "ZY"
    char t = (--n % 26  + 'A');
    res.insert(0, 1, t);
    n /= 26;
    cout << t << ' ' << n << '\n';
    }
    return res;
}