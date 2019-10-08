#include<iostream>
#include<sstream>
#include<stack>
#include<string>
#include<cctype>  // isdigit
using namespace std;

// @TODO  善于使用stream
// 1. 如何处理字符串(输入的格式可能不同)
// vector<string> 已经分割好  /  string c++中的字符串(考虑使用stringstream) /  char* c字符串(结尾'\0')
// string 读取到多位数: 采用连续读取数字的方式( )

// 2. https://leetcode.com/problems/expression-add-operators/
//   https://www.cnblogs.com/grandyang/p/4814506.html  太难了 暂时不做

namespace InfixToPost {
// https://oi-wiki.org/misc/expression/#_2  标答
// http://www.nowamagic.net/librarys/veda/detail/2307
// 基本思路: 维护 数值栈 + 运算符栈(包含优先级)  ==>
// a. 如何 中缀到后缀转换 -> 后缀计算
//   http://www.nowamagic.net/librarys/veda/detail/2307 -- 图示
//   1.遇到操作数，直接输出
//   2.栈为空时，遇到运算符，入栈
//   3.遇到左括号，将其入栈
//   4.1 遇到右括号，执行出栈操作，并将出栈的元素输出，直到弹出栈的是左括号，左括号不输出
//   4.2 遇到其他运算符’+”-”*”/’时，弹出所有优先级大于或等于该运算符的栈顶元素，然后将该运算符入栈
//   5.最终将栈中的元素依次出栈，输出
//   e.g.：a+b*c+(d*e+f)g ———> abc*+de*f+g*+

int level(char op) {
    int weight = -1;
    switch(op) {
        case '+':
        case '-':
                weight = 1;
                break;
        case '*':
        case '/':
                weight = 2;
                break;
    }
    return weight;
}

// leetcode 224 可以利用转换后缀的方式
std::string convert(const std::string &s) {  // 把中缀表达式转换为后缀表达式
  std::stack<char> oper;
  std::stringstream ss; //  @NOTE 可以方便的吐出(不用考虑空格 和 多位数字的情况)
  ss << s;
  std::string t, tmp;
  while (ss >> tmp) {
    if (isdigit(tmp[0]))
      t += tmp + " ";  // 1. 如果遇到一个数，输出该数
    else if (tmp[0] == '(')
      oper.push(tmp[0]);       // 2. 如果遇到左括号，把左括号入栈
    else if (tmp[0] == ')') {  // 3. 如果遇到右括号，
      while (!oper.empty() && oper.top() != '(')
        t += std::string(1, oper.top()) + " ",
            oper.pop();  // 不断取出栈顶并输出，直到栈顶为左括号，
      oper.pop();        // 然后把左括号出栈
    } else {             // 4. 如果遇到运算符
      while (!oper.empty() && level(oper.top()) >= level(tmp[0]))
        t += std::string(1, oper.top()) + " ",
            oper.pop();  // 只要栈顶符号的优先级不低于新符号，就不断取出栈顶并输出
      oper.push(tmp[0]);  // 最后把新符号进栈
    }
  }

  while (!oper.empty())
    t += std::string(1, oper.top()) + " ", oper.pop();
  return t;
}

int calc(const std::string &s) {  // 计算转换好的后缀表达式
  std::stack<int> num;
  std::stringstream ss;
  ss << s;
  std::string t, tmp;
  while (ss >> tmp) {
    if (isdigit(tmp[0]))       // <cctype>: isdigit isalpha isalnum
      num.push(stoi(tmp));
    else {
      int b, a;  // 取出栈顶元素，注意顺序
      if (!num.empty()) b = num.top();
      num.pop();
      if (!num.empty()) a = num.top();
      num.pop();
      if (tmp[0] == '+') num.push(a + b);
      if (tmp[0] == '-') num.push(a - b);
      if (tmp[0] == '*') num.push(a * b);
      if (tmp[0] == '/') num.push(a / b);
    }
  }
  return num.top();
}

}

// 中缀 表达式中只有加减号，数字，括号和空格  -- 引入正负号 计算结果
// https://www.cnblogs.com/grandyang/p/4570699.html
namespace BasicCalc1 {

//    |       |   |
//  2 - (6 + 3) + 1
int calculate1(string s) {
    int res = 0, num = 0, sign = 1, n = s.size();
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c >= '0') {
            num = 10 * num + (c - '0');
        } else if (c == '+' || c == '-') {   //  前一个是数字, 当前是其他字符(+. -. ). )  说明可以处理num数字
            res += sign * num;         // ----
            num = 0;
            sign = (c == '+') ? 1 : -1;
        } else if (c == '(') {
            st.push(res);
            st.push(sign);
            res = 0;
            sign = 1;
        } else if (c == ')') {
            res += sign * num;                   //   -----
            num = 0;
            res *= st.top(); st.pop();
            res += st.top(); st.pop();
        }
    }
    res += sign * num;       // -----
    return res;
}

int calculate(string s) {
    int res = 0, n = s.size(), sign = 1;
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == ' ') continue;  // 1. blank
        else if (::isdigit(c)) { // 2. digit
            int num = 0;
            while (i < n && ::isdigit(s[i])) {
                num = 10 * num + (s[i++] - '0');
            }
            res += sign * num;
            --i;
        } else if (c == '+') {
            sign = 1;
        } else if (c == '-') {
            sign = -1;
        } else if (c == '(') {       // 像是 函数调用的压栈和出栈
            st.push(res);
            st.push(sign);
            res = 0;
            sign = 1;
        } else if (c == ')') {
            res *= st.top(); st.pop();  // 确定符号
            res += st.top(); st.pop();
        }
    }
    return res;
}

}

// 中缀 表达式中+-*/ 数字和空格
// https://www.cnblogs.com/grandyang/p/4601208.html
namespace BasicCalc2 {
//  3 + 5 / 2
int calculate(string s) {
    long res = 0, num = 0, n = s.size();
    char op = '+';
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] >= '0')
            num = num * 10 + s[i] - '0';
        //                 这个地方判断不是空白 "3/2 " 这种边界条件没有考虑
        if ((s[i] < '0' && s[i] != ' ') || i == n - 1) {  // @NOTE 没有用else if 因为判断到最后 n-1 的时候是数字需要处理
            if (op == '+') st.push(num);
            else if (op == '-') st.push(-num);
            else if (op == '*' || op == '/') {
                int tmp = (op == '*') ? st.top() * num : st.top() / num;
                st.pop();
                st.push(tmp);
            }
            op = s[i];
            num = 0;
        }
    }

    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    return res;
}

int calculate(string s) {
    istringstream in('+' + s + '+');
    long long total = 0, term = 0, n;
    char op; // 以op为分隔符 提取数字
    while (in >> op) {
        if (op == '+' or op == '-') {
            total += term;
            in >> term;
            term *= (op=='+' ?1:-1);
        } else {
            in >> n;
            if (op == '*')
                term *= n;
            else
                term /= n;
        }
    }
    return total;
}

}

int main() {
    {
        using namespace std;
        using namespace InfixToPost;
        string expression  = " 9 + ( 3 - 1 ) * 3 + 10 / 2 ";
        cout << "infix version: " << expression << endl;
        // cout << "Enter infix Expression \n";
        // getline(cin,expression);
        string post = convert(expression);
        cout << "postfix version: " << post << endl;
        int result = calc(post);
        cout<<"Output = "<< result <<"\n";
    }

    {
        using namespace BasicCalc1;
        cout << calculate1(string(" 2-1 + 2 ")) << endl;
        cout << calculate1(string("(1-(4+2)-3)")) << endl;
    }
    return 0;
}