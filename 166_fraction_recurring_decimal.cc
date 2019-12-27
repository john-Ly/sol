#include <string>
#include <cstdlib>  // labs (long) 取绝对值
#include <iostream>
#include <unordered_map>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4238577.html
// 写成分数的都是有理数，而有理数要么是有限的，要么是无限循环小数
// 无限不循环的叫无理数，例如圆周率pi或自然数e等

// https://leetcode.com/problems/fraction-to-recurring-decimal/discuss/51160/C%2B%2B-unordered_map
// corner-case:  overflow (-2147483648 / -1)
string fractionToDecimal(int numerator, int denominator) {
    if (!numerator) {  // 1. 分子为0
        return "0";
    }
    string ans;
    if (numerator > 0 ^ denominator > 0) {   // 2. 分子和分母异号
        ans += '-';
    }
    // int 型整数 负数最小值取绝对值 会超出范围 -> long
    long n = labs(numerator), d = labs(denominator);

    // 3. 商
    ans += to_string(n / d);
    long r = n % d;
    // 4. 余数存在
    if (!r) { return ans; }
    ans += '.';

    // key: 当前余数   value: 余数对应的小数位置
    unordered_map<long, int> rs;
    while (r) {                       // r==0 有限循环
        if (rs.find(r) != rs.end()) { // 无限循环
            ans.insert(rs[r], "(");
            ans += ')';
            break;
        }
        // 2/3 = 0.6666
        rs[r] = ans.size();
        r *= 10;
        ans += to_string(r / d);
        r %= d;
    }
    return ans;
}

int main() {
    cout << fractionToDecimal(3, 2) << '\n';
    cout << fractionToDecimal(2, 3) << '\n';

    cout << fractionToDecimal(7, 20) << '\n';
    cout << fractionToDecimal(7, 22) << '\n';

    return 0;
}
