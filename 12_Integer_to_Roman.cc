#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. 本题限制了输入数字范围，故还有一种利用贪婪算法的解法，建立一个数表，每次通过查表找出当前最大的数，减去再继续查表
// 2.

string intToRoman(int num) {
    string res = "";
    const static vector<char> roman{'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    const static vector<int> value {1000, 500, 100, 50,  10,  5,   1};
    for (int n = 0; n < 7; n += 2) {
        int x = num/value[n];  // 取商法分别提取各个位上的数字
        if(x < 4) { // 允许重复三次
            for (int i=1; i<=x; i++)
                res = res + roman[n];
        } else if(x == 4) { // num范围[1, 3999]
            res = res + roman[n] + roman[n-1];
        } else if(x>4 && x<9) {
            res = res + roman[n-1];
            for (int i=6; i<=x; i++)
                res = res + roman[n];
        } else if(x == 9) {
            res = res + roman[n] + roman[n-2];
        }

        num %= value[n];
    }

   return res;
}

string intToRoman2(int num) {
    string res = "";
    vector<int> val{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    vector<string> str{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < val.size(); ++i) {
        while (num >= val[i]) {
            num -= val[i];
            res += str[i];
        }
    }
    return res;
}

string intToRoman3(int num) {
    string res = "";
    vector<string> v1{"", "M", "MM", "MMM"};
    vector<string> v2{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    vector<string> v3{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    vector<string> v4{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    return v1[num / 1000] + v2[(num % 1000) / 100] + v3[(num % 100) / 10] + v4[num % 10];
}


int main() {
    cout << "58 => " << intToRoman(58) << endl;
    cout << "3999 => " << intToRoman(3999) << endl;
    cout << "1994 => " << intToRoman(1994) << endl;

    return 0;
}
