// https://blog.csdn.net/sxhelijian/article/details/8978850
// https://blog.csdn.net/qiao1245/article/details/53020326
// https://blog.csdn.net/qq_31467305/article/details/100033440

// 包含所有头文件
#include <bits/stdc++.h>

// 快速输出一个数组
#include <iterator>
std::copy(v.begin(), v.end(),
        std::ostream_iterator<int>(cout, ","));
cout << endl;


#include <iostream>
using namespace std;

// 2. 多行输入 (最后一组输入非法数据)
int a,b;                   // ab 满足某种非法输入
while ((cin >> a >> b) && (a && b)) {
    cout << a+b << endl;
}

// 3. 指定行数
int a, b, n;
cin >> n;
// 接受来自输入的数据(空格分开) 放入数组
vector<int> v;
v.resize(n);
for (auto& i: v) cin >> i;

for(i=0;i<n;i++) {
    cin >> a >> b;
    cout << a + b << endl;
}

// 暂存文件 直接在文件输入
#include<cstdio>
{
    freopen("input.txt","r",stdin);  //只加这一句输入将被重定向到文件input.txt
    int a,b;
    cin>>a>>b;
    cout<<a+b<<endl;
}

{
// https://blog.csdn.net/qq_38906523/article/details/79823057
// 输入不定量的字符串
string str;
while(cin>>str)
}

// https://www.cnblogs.com/expedition/p/11616279.html
// 进行整数类型和字符串的转换
{
    stringstream sstream;
    string strResult;
    int nValue = 1000;
    // 将int类型的值放入输入流中
    sstream << nValue;
    // 从sstream中抽取前面插入的int类型的值，赋给string类型
    sstream >> strResult;
}

{
    stringstream sstream;
    // 将多个字符串放入 sstream 中
    sstream << "first" << " " << "string,";
    sstream << " second string";
    cout << "strResult is: " << sstream.str() << endl;
    sstream.str("")  // 清空流的字符串
}

#include <iostream>
#include <sstream>
using namespace std;
int main() {
	vector<string> res;
	string s;
    // 从输入 分割字符串


{
    // 从用户输入读入 255个字符 默认换行符号结束
    char buf[ 255 ];
    while(cin.getline( buf, 255));
}

	getline(cin, s);  // 读入一行字符串
	stringstream ss(s);   //字符串流

    // 按行读取
    // 按照空格解析单词
	while (getline(ss, s, ' ')) {
		res.push_back(s);
		cout << s << endl;
	}
	while (!getchar());  //等待输入
	return 0;
}

// https://zhuanlan.zhihu.com/p/48214012
 // 解析cxv文件 对逗号的处理
// stringstream.str()
	string a = "1+1i", b = "1+1i";
	int  ra, ia, rb, ib;
	char buff;
	stringstream aa(a), bb(b), ans;
	aa >> ra >> buff >> ia >> buff;
	bb >> rb >> buff >> ib >> buff;
	ans << ra * rb - ia * ib << "+" << ra * ib + rb * ia << "i";
	cout << ans.str();
	while (!getchar());
	return 0;