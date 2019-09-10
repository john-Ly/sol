#include <string>  // to_string();  itoa
#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4395356.html

string multiply(string num1, string num2) {
    string res = "";
    int m = num1.size(), n = num2.size();
    vector<int> vals(m + n);
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            // p2是低位 p1是高位  因为字符串存储的数字 [0, n-1] -> [高位, 低位]
            int p1 = i + j, p2 = i + j + 1, sum = mul + vals[p2];
            vals[p1] += sum / 10;
            vals[p2] = sum % 10;
            // 保证低位都是个位数(即取模后 最终的结果)
        }
    }
    // 两位数相乘 最大只能到4位数  所以最高位肯定不会超过

    for (int val : vals) {
        //  非空 0合法  +   空 找到第一个非0数字 合法
        if (!res.empty() || val != 0) res.push_back(val + '0');
    }
    return res.empty() ? "0" : res;
}

int main() {
    string a = "123", b = "456";
    cout << multiply(a, b) << endl;
    return 0;
}