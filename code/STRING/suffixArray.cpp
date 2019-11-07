#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;


// 二分搜索算法
// https://www.cnblogs.com/grandyang/p/6854825.html

struct SuffixComparator {
	const string s;
	SuffixComparator(const string& s) : s(s) { }
	bool operator() (int i, int j) {
		// 不用 s.substr() 使用 strcmp() 函数, 能够减少生成临时对象的开销
		return strcmp(s.c_str()+i, s.c_str()+j) < 0;
	}
};

/*
    std::vector<const char*> cats {"Heathcliff", "Snagglepuss", "Hobbes", "Garfield"};
    std::sort(cats.begin(), cats.end(), [](const char *strA, const char *strB) {
        return std::strcmp(strA, strB) < 0;
    });  //--------> strcmp 默认是按照字典排序 ( lhs < rhs )

        Negative value if lhs appears before rhs in lexicographical order.
        Zero if lhs and rhs compare equal.
        Positive value if lhs appears after rhs in lexicographical order.

    for (const auto *cat : cats) {
        std::cout << cat << '\n';
    }
*/

// perm[i] = j ==> s[j...]  后缀数组里面存放的值 是字符串后缀的起点下标
vector<int> getSuffixArrayNaive(const string& s) {
	// 生成保存后缀起始位置的数组
	vector<int> perm;
	for(int i=0; i<s.size(); ++i)
		perm.push_back(i);
	// 利用比较后缀的比较符排序
	std::sort(perm.begin(), perm.end(), SuffixComparator(s));
	// sort() --- O(n logn)
	return perm;
}

// 利用根据前 t 个字符分类的分组信息比较浅 2t 个字符的比较符
// 给出以各后缀的前 t 个字符为标准的后缀分组序号时
// 以后缀的前 2*t 个字符为标准比较两个后缀
// group 包含长度为 0 的后缀
struct Comparator {
	vector<int> group;
	int t;
	Comparator(const vector<int>& _group, int _t) {
		group = _group; t = _t;
	}

	bool operator() (int a, int b) {
		// 如果前 t 个字符不同, 则利用不同字符比较
		if(group[a] != group[b]) return group[a] < group[b];
		// 否则比较 S[a+t ...]和 S[b+t...]的第一个字符
		return group[a+t] < group[b+t];
	}
};

// Manber-Myers 后缀数组
vector<int> getSuffixArray(const string& s) {
	int n = s.size();
	// group[i] = 以前 t 个字符为标准进行后缀排序时,
	// 包含 S[i...] 的分组序号
	// t=1时, 没有必要排序, 所以要把 S[i...]的第一个字符用作分组序号

	int t = 1;
	vector<int> group(n+1);
	for(int i=0; i<n; ++i)
		group[i] = s[i];
	group[n] = -1;
	// 最终成为后缀数组的返回值. 对此数组进行lg(n)次排序
	vector<int> perm(n);
	for(int i=0; i<n; ++i) perm[i] = i;

	while(t<n) {
		// 以前 t 个字符为标准计算group[]
		// 以前 2t 个字符为标准 重新排序perm
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		// 如果 2t 个字符超过 n, 则后缀数组的排序已完成
		t *= 2;
		if(t >= n) break;
		// 生成以前 2t 个字符为标准的分组信息
		vector<int> newGroup(n+1);
		newGroup[n] = -1;
		newGroup[ perm[0] ] = 0;
		for(int i=1; i<n; ++i) {
			if(compareUsing2T(perm[i-1], perm[i]))
		 		newGroup[ perm[i] ] = newGroup[ perm[i-1] ] + 1;
			else
				newGroup[ perm[i] ] = newGroup[ perm[i-1] ];
		}
		group = newGroup;
	}
	return perm;
}

vector<int> suffix_array_search(const string& H, const string& N) {
    vector<int> ret;
    if (N.size() < 1) return ret;

    // "banana" => 5 3 1 0 4 2
    vector<int> a = getSuffixArrayNaive(H);
    const int h = a.size();
    // N字符串 不是后缀数组里面任意一个的前缀
    if (H[a[0]] > N[0]) return ret;
    if (H[a[h-1]] < N[0]) return ret;

    const int n = N.size();
	for(int i=0; i<h/*a.size()*/; ++i) {
        // 可以优化的地方 是 找到lower_bound == 利用二分查找
        // @TODO 逆序找 找到upper_bound 再进行长度的比较(先判断长度是否满足)
		if(H[a[i]] == N[0] && n <= h-a[i] ) {
            int j = a[i], k=0;
            while(k<n && H[j] == N[k]) {
                j++; k++;
            }
            if(k == n) ret.push_back(a[i]);
		}
    }

    return ret;
}

int main() {
    // string s = "avadakedavraavadakedavra";
    // string s = "alohomora";
    string s = "banana";
    for(auto i : getSuffixArrayNaive(s) )
      	cout << i << " ";
    cout << endl;
   	for(auto i : getSuffixArray(s) )
      	cout << i << " ";
    cout << endl;

    string haystack = "banana";
    string needle = "na";
    auto tmp = suffix_array_search(haystack, needle);
    for (auto i: tmp)
        cout << i << " ";
    cout << endl;

	return 0;
}
