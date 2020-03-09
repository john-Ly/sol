#include <iostream>
#include <cstring> // memset()
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using std::cout;
using std::endl;


// leetcode 208/ 212  word search
// 在N个元素的BST查 search: O(lg N) 比较 每次比较都是常数级别--针对整数
//        字符串比较需要O(M) M表示字符串的长度  总的Time O(M lg N)
//
// 字典树: 表示字符串 集合的树型数据结构 "set<string>"
//
// 特点:
// 从根节点移动到某个子节点过程, 累加所有遇到的字符 就是当前节点表示的前缀
// 由于字典树包含其存储字符串的所有前缀, 类似 智能提示类的应用 输入两三个字符就能显示是否存在

// 但是占用内存太大
//
// bonus: 把terminal 换成其他数据类型: 就是map<string, Value_type>
// 效率比map更好 不过可能需要更多的内存空间
// =================================================

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

namespace upcase_alpha {

// 保存英文大写字母的字典树 每个节点可能有 26 个后代节点
struct TrieNode {
	TrieNode* children[ALPHABETS]; // 没有相应节点 保存nullptr
	bool terminal;  // 判断是否是终止节点

	TrieNode() : terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for(int i=0; i<ALPHABETS; ++i)
			if(children[i])
				delete children[i];
	}

    // insert/ find 时间复杂度
    // 会正比于字符串长度, 而不会受到含有字符串个数影响
    //
	// 向将此节点用作根节点的字典树 添加字符串 key
	void insert(const char* key){
		// 字符串处理完毕后 向 terminal 赋真值并结束
		if(*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			// 如果没有相应子节点 则生成
			if(children[next] == nullptr)
				children[next] = new TrieNode();
			// 用相应子节点递归调用
			children[next]->insert(key+1);
		}
	}

    // 不考虑找出的字符串对应节点是否是终止节点
	TrieNode* find(const char* key) {
		if(*key == 0) return this;

		int next = toNumber(*key);
		if(children[next] == nullptr)
			return nullptr;

		return children[next]->find( key+1 );
	}

};

}

// P559 输入提示
// 利用单词开始的几个字符 找出剩余字符的运算 == 利用字符串的前缀搜索词典
// 字典树 经典应用场景
namespace typing_prompt {

// 保存英文大写字母的字典树 每个节点可能有 26 个后代节点
struct TrieNode {
	TrieNode* children[ALPHABETS]; // 没有相应节点 保存nullptr
	// 在该节点终止的字符串序号 没有则为 -1
	int terminal;
	// 最先添加到该节点用作根节点的字典树的单词序号 初始化为 -1
	int first;

	TrieNode() : terminal(-1), first(-1) {
        memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for(int i=0; i<ALPHABETS; ++i)
			if(children[i])
				delete children[i];
	}

	// 将序号为 id 的字符串 key 添加到 将此节点用作根节点的字典树
	void insert(const char* key, int id) {
        std::cout << first << std::endl;
		if(first == -1) first = id;
		if(*key == 0) // 字符串结束时, 只更换 terminal 并终止
			terminal = id;
		else {
			int next = toNumber(*key);
			if(children[next] == nullptr) { children[next] = new TrieNode(); }
			children[next]->insert(key+1, id);
		}
	}

	// 键入该节点时, 为了键入序号 id 的 key (id 应该由上层封装)
	// 最少还需要敲击几次
	int type(const char* key, int id) {
		// 字符串结束时
		if(*key == 0) return 0;
		// 该节点推荐的字符串就是此字符串时, 按下标签项后终止
		if(first == id) return 1;
		// 如果不是 则继续键入下一字符
		int next = toNumber(*key);
		return 1 + children[next]->type(key+1, id);
	}

    // 不考虑找出的字符串对应节点是否是终止节点
	TrieNode* find(const char* key) {
		if(*key == 0) return this;

		int next = toNumber(*key);
		if(children[next] == nullptr)
			return nullptr;

		return children[next]->find( key+1 );
	}

};

// 给出表示词典的字典树后, 计算输入 单词word需要多少次按键
int countKeys(TrieNode* trie, const char* word) {
    // 先确认此字符串是否存在于词典中, 若存在则求序号
    TrieNode* node = trie->find(word);
    // 若词典没有此字符串 手动键入 即字符串长度
    if(node == nullptr || node->terminal == -1) return strlen(word);
    // 通过搜索找出键入方法
    return trie->type(word, node->terminal);
}

// 对输入值中的单词排序后 构建字典树
TrieNode* readInput(int words) {
	// 以出现频率的降序和字典顺序的升序排列单词
    std::vector<std::pair<int, std::string> > input;
	for(int i=0; i<words; ++i) {
		char buf[11];
		int freq;
        scanf("%s %d", buf, &freq);
		input.push_back(std::make_pair(-freq, buf));
	}

    std::sort(input.begin(), input.end());
	// 此时 越靠前的单词优先级越高
	// 将数组下标用作各单词序号
	TrieNode* trie = new TrieNode();
	for(int i=0; i<input.size(); ++i)
		trie->insert( input[i].second.c_str(), i );
	trie->first = -1;
	return trie;
}

}

int main() {
    // passed
    {
        // test trie
        const char *s[] = {"BE", "BET", "BUS", "TEA", "TEN"};
        upcase_alpha::TrieNode tmp;
        int n = sizeof(s)/sizeof(char *);
        for(int i=0; i<n; ++i)
            tmp.insert(s[i]);

        // cout << (tmp.find("BE") ? tmp.find("BE")->terminal : false) << endl;
        // cout << (tmp.find("B") ? tmp.find("B")->terminal : false) << endl;

        auto res = tmp.find("BE");
        if (res != nullptr) {
            if (res->terminal) {
                cout << "BE is exists\n";
            }
        }
    }

    // passed
    // {
    //     // sort vector<pair>
    //     using std::vector;
    //     using std::pair;
    //     using std::string;
    //     // 智能提示(根据词频和前缀进行提示)
    //     vector<pair<int, string>> freqTbl = {
    //         {4, "all"}, {3, "and"}, {8, "fish"},
    //         {6, "for"}, {4, "so"}, {9, "thanks"},
    //         {9, "the"}
    //     };

    //     auto p_v = [&freqTbl]() {
    //                    for (const auto& p : freqTbl) {
    //                        cout << p.second << '-' << p.first << endl;
    //                    }
    //                    cout << endl;
    //                };

    //     p_v();
    //     // 其实也可以pair<int> 填充负值 这样也能够降序
    //     using entry_t = pair<int, string>;
    //     std::sort(freqTbl.begin(), freqTbl.end(),
    //               [](entry_t& lhs, entry_t& rhs) {
    //                   if (lhs.first != rhs.first)
    //                     return lhs.first > rhs.first;
    //                   else
    //                     return lhs.second < rhs.second;
    //               });
    //     p_v();
    // }

    {
        using namespace typing_prompt;
        using std::vector;
        using std::pair;
        using std::string;
        // 智能提示(根据词频和前缀进行提示)
        vector<pair<int, string>> freqTbl = {
            {4, "all"}, {3, "and"}, {8, "fish"},
            {6, "for"}, {4, "so"}, {9, "thanks"},
            {9, "the"}
        };

        using entry_t = pair<int, string>;
        std::sort(freqTbl.begin(), freqTbl.end(),
                  [](entry_t& lhs, entry_t& rhs) {
                      if (lhs.first != rhs.first)
                        return lhs.first > rhs.first;
                      else
                        return lhs.second < rhs.second;
                  });

        // TrieNode* trie = new TrieNode{};
        typing_prompt::TrieNode trie;
        for(int i=0; i<freqTbl.size(); ++i)
        // @TODO bug insert(thanks)
        // first 没有初始化完全
        // #0  0x00005555555582d8 in typing_prompt::TrieNode::insert (this=0x6f73, key=0x555555573329 "hanks", id=0) at trie.cpp:104
        // #1  0x0000555555558378 in typing_prompt::TrieNode::insert (this=0x7fffffffd990, key=0x555555573328 "thanks", id=0) at trie.cpp:110
        // #2  0x0000555555556948 in main () at trie.cpp:250
            trie.insert(freqTbl[i].second.c_str(), i);
        trie.first = -1;

        vector<string> inputTbl = {
            {"so"}, {"long"}, {"and"},
            {"thanks"}, {"for"}, {"all"}, {"the"}, {"fish"}
        };

        // 最终运算结果也是错误 @BUG
        int ret = 0;
        for(auto& s : inputTbl) {
            ret += countKeys(&trie, s.c_str());
        }
        cout << ret << endl;
    }

	return 0;
}
