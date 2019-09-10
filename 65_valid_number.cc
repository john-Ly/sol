#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

// 有限自动机 是 好东西(DFA)
// 最关键是如何分析题目 如何画出来
// https://leetcode.com/problems/valid-number/discuss/23728/A-simple-solution-in-Python-based-on-DFA

bool isNumber(string s) {
    // 状态转移表 从1开始计数
    static vector<unordered_map<string, int>> states = {
        {}, //state 0
        {{"blank", 1}, {"sign", 2}, {"digit", 3}, {"dot", 4}}, //state 1
        {{"digit", 3}, {"dot", 4}}, //state 2
        {{"digit", 3}, {"dot", 5}, {"e", 6}, {"blank", 9}}, //state 3, final
        {{"digit", 5}}, //state 4
        {{"digit", 5}, {"e", 6}, {"blank", 9}}, //state 5, final
        {{"sign", 7}, {"digit",8}}, // state 6
        {{"digit", 8}}, //state 7
        {{"digit", 8}, {"blank", 9}}, //state 8, final
        {{"blank", 9}} // state 9, final
    };

    int currState = 1; string transition;
    for(auto c : s) {
        // 所有元素
        if(c>='0' && c<='9') transition = "digit";
        else if(c=='-' || c=='+') transition = "sign";
        else if(c == ' ') transition = "blank";
        else if(c == '.') transition = "dot";
        else if(c == 'e' || c == 'E') transition = "e";
        else return false;

        auto it = states[currState].find(transition);
        if(it == states[currState].end()) return false;
        else currState = it->second;
    }

    if(currState == 3 || currState == 5 || currState == 8 || currState == 9) return true;
    else return false;
}

int main() {
    cout << "0 => " <<  isNumber("0") << endl;
    cout << "0.1 => " <<  isNumber("0.1") << endl;
    cout << "abc => " <<  isNumber("abc") << endl;
    cout << "1 a => " <<  isNumber("1 a") << endl;
    cout << "2e10 => " <<  isNumber("2e10") << endl;
    cout << "2e-10 => " <<  isNumber("2e-10") << endl;
    cout << "-20e10 => " <<  isNumber("-20e10") << endl;
    cout << "2e => " <<  isNumber("2e") << endl;
    cout << "+e1 => " <<  isNumber("+e1") << endl;
    cout << "1+e => " <<  isNumber("1+e") << endl;
    cout << "e3 => " <<  isNumber("e3") << endl;
    cout << "6e-3 => " <<  isNumber("6e-3") << endl;
    cout << "99e2.4 => " <<  isNumber("99e2.4 ") << endl;
    cout << "99.9e24 => " <<  isNumber("99.9e24") << endl;
    cout << "--4 => " <<  isNumber("--4") << endl;
    cout << "-+4 => " <<  isNumber("-+4") << endl;
    cout << "95a54e53 => " <<  isNumber("95a54e53") << endl;
    cout << " => " <<  isNumber(" ") << endl;
    cout << " => " <<  isNumber("") << endl;
    cout << " => " <<  isNumber("") << endl;
    cout << " => " <<  isNumber("") << endl;
    cout << " => " <<  isNumber("") << endl;
    cout << "-e10 => " <<  isNumber("-e10") << endl;
    /*
string s11 = "e9"; // False
string s12 = "4e+"; // False
string s13 = " -."; // False
string s14 = "+.8"; // True
string s15 = " 005047e+6"; // True

string s16 = ".e1"; // False
string s17 = "3.e"; // False
string s18 = "3.e1"; // True
string s19 = "+1.e+5"; // True
string s20 = " -54.53061"; // True

string s21 = ". 1"; // False
*/
    return 0;
}
