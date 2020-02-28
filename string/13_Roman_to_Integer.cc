#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

// 1. string 其实就是 vector<char> 因此可以尽可能利用 .back()等函数
// 2. 输入的字符串一定是罗马字符 否则还要自己判断
//
// @TODO 递归的求解

int romanToInt(string s) {
    // 使用static节省空间
   static unordered_map<char, int> T = { { 'I' , 1 },
                                   { 'V' , 5 },
                                   { 'X' , 10 },
                                   { 'L' , 50 },
                                   { 'C' , 100 },
                                   { 'D' , 500 },
                                   { 'M' , 1000 } };

    /* 换成数组 节省空间
        int value[128];
        value['I'] = 1;
        value['V'] = 5;
        value['X'] = 10;
        value['L'] = 50;
        value['C'] = 100;
        value['D'] = 500;
        value['M'] = 1000;
    */

   int sum = T[s.back()];
   // 倒序判断
   for (int i=s.length()-2; i>=0; --i) {
       if (T[s[i]] < T[s[i + 1]]) {
           sum -= T[s[i]];
       } else {
           sum += T[s[i]];
       }
   }

   return sum;
}

int main() {
    cout << "MCMXCIV => " << romanToInt("MCMXCIV") << endl;
    cout << "LVIII => " << romanToInt("LVIII") << endl;

    return 0;
}
