#include <cctype> // isalnum()
#include <string>
#include <iostream>
using namespace std;

/*  回文字符串的判断 BinaryPredicate(可以自定义比较)
 hash 表不能用于判断 因为hash bucket里面的内容可能不同

#include <algorithm>
bool is_palindrome(const std::string& s) { return std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin()); }

int main() {
    test("radar");
    test("hello");
}
*/

// 0-9: [48, 57]   0x30    '0' 和 'P'之间相差32所以 会造成错误
// A-Z: [65, 90]   0x41
// a-z: [97, 122]  0x61
bool equal(const char a, const char b) {
    if( a==b || a-b == 32 || b-a == 32)
        return true;
    return false;
}

// 因为判断回文前和后 字符都有可能非数字和字母 所以每次循环都要判断是否是合法字母_数字
// @NOTE 跟以往不同的地方是  可能一个while循环找到合法字符后
bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1 ;
    while (left < right) {

        // 1. 先判断左边
        if (!isalnum(s[left]))  {++left;}
        // 2. 再判断右边(1条件成立)
        else if (!isalnum(s[right])) {--right;}
        // 3. 判断是否相等 (0-9 与大写字母 P-Y 不会干扰)
        // 有点绕
        else if ((s[left] + 32 - 'a') %32 != (s[right] + 32 - 'a') % 32) {
       // else if (!equal(s[left], s[right])) {
            // cout << "edn" << endl;
            return false;
        }
        // 4.相等就各自 "向前"
        else {
            // cout << s[left] << "-" << s[right] << endl;
            ++left; --right;
        }
    }
    return true;
}

namespace sol_266 {

// 字符串的某个排列是否包含回文
bool canPermutePalindrome(string s) {
    unordered_map<char, int> m;
    int cnt = 0;
    for (auto a : s) ++m[a];
    for (auto a : m) {
        if (a.second % 2 != 0) ++cnt;
    }
    // 偶数个字符       奇数个字符
    return cnt == 0 || (s.size()%2 != 0 && cnt == 1);
}
}

int main () {
    /*
    string s = "0pPp";
    cout << equal(s[0], s[1]) << endl;
    cout << equal(s[2], s[1]) << endl;
    cout << equal(s[3], s[1]) << endl;
    */

    string t = "A man, a plan, a canal: Panama";
    string r = "0P";
    cout << isPalindrome(t) << endl;
    cout << isPalindrome(r) << endl;


    return 0;
}
