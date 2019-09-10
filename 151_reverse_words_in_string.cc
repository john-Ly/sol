#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// @TODO 熟悉 std::reverse算法
// 字符串初始化 和 string s = “”有什么区别

// https://www.cnblogs.com/grandyang/p/4606676.html
// c的做法 没有尝试 @TODO 不过getline函数已经简化了很多
//
// https://www.cnblogs.com/grandyang/p/5186294.html
// - 翻转字符串(先把每个单词进行翻转 然后翻转整个字符串)

// https://www.cnblogs.com/grandyang/p/6703311.html
// - 翻转字符串中的每个单词(可以考虑)

// 中间的空格简化成一个空格
// 首尾空格省掉
// 如果有多个空格字符连在一起，那么t会赋值为空字符串
string reverseWords(string s) {
    string res, tmp;
    stringstream ss(s);
    while(getline(ss,tmp,' ')) {
        cout << tmp << endl;
        if(tmp.empty()) continue;

        // 有点像头插法
        res = ( res.empty() ? tmp : (tmp+" "+res) );
    }

    return res;
}

string reverseWords2(string s) {
    // istringstream可以使用>>操作符
    istringstream is(s);
    string tmp, res;
    // 提取连在一起的非空格字符  (即words, 排除特殊字符)
    is >> res;
    cout << res << endl;
    while(is >> tmp) res = tmp + " " + res;

    // istringstream接收的是空字符串 因此会成
    // @TODO 空串和之含有空格的字符串
    // 字符串没有识别出来(仅含有空格的string)
    // Checks if the string has no characters = ""
    if(!res.empty() && res[0] == ' ') {
        cout << res.size() << endl;
        res = "";
    }

    return res;
}

int main() {
    cout << reverseWords2("the sky is blue") << endl;
    cout << "===" << endl;
    cout << reverseWords2("  hello world!   ") << endl;
    cout << "===" << endl;
    cout << reverseWords2("a good   example") << endl;
    cout << "===" << endl;
    cout << reverseWords2("    ") << endl;
    cout << "===" << endl;
    return 0;
}