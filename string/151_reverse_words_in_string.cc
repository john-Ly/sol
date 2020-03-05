#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

namespace {
// 原地翻转 @SEE 189
void reverse_array(string &s) {
	int n = s.length();
	for (int i = 0; i < n/2; i++)
		std::swap(s[i], s[n-i-1]);
}
}

// https://www.cnblogs.com/grandyang/p/4606676.html
// c的做法 没有尝试 @TODO 不过getline函数已经简化了很多
//
// https://www.cnblogs.com/grandyang/p/5186294.html
// - 翻转字符串(先把每个单词进行翻转 然后翻转整个字符串)

// https://www.cnblogs.com/grandyang/p/6703311.html
// - 翻转字符串中的每个单词(可以考虑)

namespace reverse_sentence {
// 中间的空格简化成一个空格
// 首尾空格省掉
// 如果有多个空格字符连在一起，那么t会赋值为空字符串
// " the   sky is blue"
// "blue is sky the"

// stringstream + getline 自动识别空格
string reverseWords_ss(string s) {
    string res, tmp;
    stringstream ss(s);
    while( getline(ss, tmp, ' ') ) {
        if(tmp.empty()) continue;
        res = ( res.empty() ? tmp : (tmp+" "+res) );
    }
    return res;
}

// 先整体反转 在针对每个单词进行反转
// 假定所有的单词之间 只有一个空格; 首尾无空格(可以方便的剔除)
string reverseWords2(string s) {
    reverse_array(s);
    for (int i=0,j=0; i<s.size(); i=j+1) {
        for(j=i; i<s.size(); ++j) {
            if (s[j] == ' ') break;
        }
        std::reverse(s.begin()+i, s.begin()+j)
    }
}

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