#include <string>  // to_string();  itoa
#include <iostream>
#include <algorithm>
using namespace std;

// @NOTE 格雷码  异或实际是模加法(二进制)
// Another way: the digit is 1 if adigit + bdigit + carry == 1 or == 3, but I noticed that
// XOR is more concise:
//

// https://www.cnblogs.com/grandyang/p/4084971.html
// 用了两个指针分别指向a和b的末尾，然后每次取出一个字符，转为数字，若无法取出字符则按0处理，然后定义进位carry，初始化为0，
// 将三者加起来，对2取余即为当前位的数字，对2取商即为当前进位的值
// 记得最后还要判断下carry，如果为1的话，要在结果最前面加上一个1
string addBinary(const string& a, const string& b) {
    string res = "";
    int m = a.size() - 1, n = b.size() - 1, carry = 0;
    while (m >= 0 || n >= 0) { // (|| carry == 1)
        // 因为两个字符串长度不同  短的字符串高位要全部补0
        int p = m >= 0 ? a[m--] - '0' : 0;
        int q = n >= 0 ? b[n--] - '0' : 0;

        int sum = p + q + carry;
        res = to_string(sum % 2) + res;
        carry = sum / 2;
    }
    return carry == 1 ? "1" + res : res;
}

// https://www.cnblogs.com/grandyang/p/5944311.html
// leetcode-415
string addStrings(string num1, string num2) {
    string res = "";
    int m = num1.size(), n = num2.size(), i = m - 1, j = n - 1, carry = 0;
    while (i >= 0 || j >= 0) {
        int a = i >= 0 ? num1[i--] - '0' : 0;
        int b = j >= 0 ? num2[j--] - '0' : 0;
        int sum = a + b + carry;
        res.insert(res.begin(), sum % 10 + '0');
        carry = sum / 10;
    }
    return carry ? "1" + res : res;
}

string addBinary2(string a, string b) {
    string res = "";
    int na = a.size(), nb = b.size();
    int n = max(na, nb);
    bool carry = false;

    // 可能两个字符串长度不同  短的字符串高位要全部补0
    // @TODO 字符串insert()函数 插入特定位置
    if (na > nb) {
        for (int i = 0; i < na - nb; ++i) b.insert(b.begin(), '0');
    } else if (na < nb) {
        for (int i = 0; i < nb - na; ++i) a.insert(a.begin(), '0');
    }

    for (int i = n - 1; i >= 0; --i) {
        int tmp = 0;
        if (carry) tmp = (a[i] - '0') + (b[i] - '0') + 1;
        else tmp = (a[i] - '0') + (b[i] - '0');

        if (tmp == 0) {
            res.insert(res.begin(), '0');
            carry = false;
        } else if (tmp == 1) {
            res.insert(res.begin(), '1');
            carry = false;
        } else if (tmp == 2) {
            res.insert(res.begin(), '0');
            carry = true;
        } else if (tmp == 3) {   // 1+1 同时之前还有进位
            res.insert(res.begin(), '1');
            carry = true;
        }
    }

    return carry ? "1" + res : res;
}

int main() {
    string a = "1010", b = "1011";
    cout << addBinary2(a, b) << endl;
    cout << addStrings(a, b) << endl;
    return 0;
}