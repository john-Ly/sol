#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

#define Size 50
int cnt = 0;

// wildcard/ regex放弃了 理解不了为什么出现错误
// https://www.cnblogs.com/grandyang/p/4401196.html
// https://www.cnblogs.com/grandyang/p/4461713.html
// 穷举搜索
bool match(const string& w, const string& s) {
	int pos = 0;
	/* 1. 含有 ? 的范式 == 长度相同
	 * 2. 已经到达 范式 的最后一个字符
	 *     范式可能包含 * 或者 不包含(w.size == s.size-->匹配)
	 * 3. 到达 s 的最后一个字符
	 *     范式可能包含 * 或者 不匹配
	 */

	// 遇到 * 或者 字符串结束为止
	while(pos<s.size() && pos<w.size() &&
 	    (w[pos] == '?' || w[pos] == s[pos]))
 	    ++pos;

	// 已达到范式最后一个字符 字符串也到最后一个字符 匹配
    if(pos == w.size())
        return pos == s.size();

    // 遇到 * 结束循环 --- 利用递归调用 查看 * 对应多少个字符
    // @see substring_func.cpp
	if(w[pos] == '*')
	    for(int skip=0; pos+skip<=s.size(); ++skip) {
	    	cnt++;
            cout << "pos: " << pos << ' ' << w.substr(pos+1) << '\t' << s.substr(pos+skip) << ' ' << skip << '\n';
	    	if( match(w.substr(pos+1), s.substr(pos+skip)) ) {
				return true;
			}
		}

	// 除此之外所有关系不成立
	return false;
}

// 动态规划
/* -1 表示还未计算
 *  1 表示输入值存在对应关系
 *  0 表示输入没有对应关系
 */
int cache[Size][Size];
string W, S;
bool matchMemoized(int w, int s) {
    // 1.初始部分+错误处理
    // ...

    // 2. cache存在,直接返回
	int& ret = cache[w][s];
	if(ret != -1)
        return ret;

    // 3. 求解
	while(s<S.size() && w<W.size() &&
 	    (W[w] == '?' || W[w] == S[s])) {
		++s; ++w;
	}

	// 已达到范式最后一个字符 字符串也到最后一个字符 匹配
    if(w == W.size())
        return ret = (s == S.size());

    // 遇到 * 结束循环 --- 利用递归调用 查看 * 对应多少个字符
	if(W[w] == '*') {
	    for(int skip=0; s+skip<=S.size(); ++skip) {
	    	cnt++;
            cout << w+1 << '\t' << s+skip << ' ' << skip << '\n';
            ////// 这里定义了子问题 因为子问题和问题只是少了一些计算 因此可以利用递归
			if( matchMemoized(w+1, s+skip) ) {
				return ret = 1;
            }
            ////// 子问题
        }
    }
	// 除此之外所有关系不成立
	return ret = 0;
}

bool faster_matchMemoized(int w, int s) {
    cnt++;
	int& ret = cache[w][s];
	if(ret != -1)
        return ret;

	while(s<S.size() && w<W.size() &&
 	    (W[w] == '?' || W[w] == S[s])) {
		return ret = faster_matchMemoized(w+1, s+1);
	}

	// 已达到范式最后一个字符 字符串也到最后一个字符 匹配
    if(w == W.size())
        return ret = (s == S.size());

    // 遇到 * 结束循环 --- 利用递归调用 查看 * 对应多少个字符
	if(W[w] == '*')
	    if( faster_matchMemoized(w+1, s) || (s<S.size() && faster_matchMemoized(w, s+1)) )
			return ret = 1;

	// 除此之外所有关系不成立
	return ret = 0;
}


int main() {
	string s = "hlep";
	string w = "hl?p";
	// W = "*bb*";
	// S = "babbbc";
 	// W = "t*l?*o*r?ng*s";
	// S = "thelordoftherings";

	/* recursive
	s s 0
	r?ng*s rings 4
	o*r?ng*s oftherings 2
	l?*o*r?ng*s lordoftherings 2
	cnt: 12
	*/
	// time-cosumption test
 	// cnt: 18563

	W = "******a";
	S = "aaaaaaaaaab";
	/*
	brute-force:
	0
	341149445
	--------------------------------
	Process exited after 68.17 seconds with return value 0
	*/
	// S = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
	// W = "a*******b";

    ::memset(cache, -1, sizeof(cache));
	// for(int i=0; i<Size; ++i)
	// 	for(int j=0; j<Size; ++j)
	// 	    cache[i][j] = -1;

    cout << W << '\t' << S << '\n';
	cout << "brute-force:\n";
	// cout << match(W, S) << endl;
	cout << faster_matchMemoized(0, 0) << endl;
    // cout << matchMemoized(0, 0) << endl;
	cout << cnt << '\n';
    return 0;
}
