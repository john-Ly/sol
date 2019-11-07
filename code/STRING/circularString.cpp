#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

// 比较两个字符串 最多会耗费正比与字符串长度的时间  O(n)
struct SuffixComparator {
	const string s;
	SuffixComparator(const string& s) : s(s) { }
	bool operator() (int i, int j) {
		// 不用 s.substr() 使用 strcmp() 函数, 能够减少生成临时对象的开销
		return strcmp(s.c_str()+i, s.c_str()+j) < 0;
	}
};

// time: O(n^2 logn)
vector<int> getSuffixArrayNaive(const string& s) {
	// 生成保存后缀起始位置的数组
	vector<int> perm;
	for(int i=0; i<s.size(); ++i)
		perm.push_back(i);
	// 利用比较后缀的比较符排序
	std::sort(perm.begin(), perm.end(), SuffixComparator(s));
	// sort() --- O(n logn)
    // sort会进行O(n logn)此比较
	return perm;
}

// 在长度至少为n的后缀中找出最前面的后缀 // 后缀数组本身就是 字典序
// s ->  s+s
// O(n^2 * lg n)
string minShift(const string& s) {
	string s2 = s + s;
	vector<int> a = getSuffixArrayNaive(s2);
    int n = s.size();
	for(int i=0; i<n/*a.size()*/; ++i) {
        // 主要理解 <n 的情形 应该是处于一般 而且首字母不是 a 之类
		if(a[i] <= n) {
            // substr(): String containing the substring [pos, pos+count)
            // pos: 起始位置 count: 取出count个字符
			return s2.substr(a[i], n);
			// @TODO 为什么 不是 abc --> abcabc --> a的存放顺序是什么...
		}
    }
	// 不能执行到此位置
	return "__oops__";
}

int main() {
    string s = "avadakedavra";
   	cout << minShift(s) << " ";

	return 0;
}
