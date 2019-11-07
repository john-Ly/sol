#include <iostream>
#include <cstring> // memset()
using namespace std;

/*
//#include <cstring>
const char str[] = "How many characters does this string contain?";

std::cout << "without null character: " << std::strlen(str) << '\n'
         << "with null character: " << sizeof str << '\n';
*/

// 表示字典树节点的对象的声明方法 
// ================================================= 
// 保存英文大写字母 每个节点可能有 26 个后代节点
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// 表示字典树的一个节点的对象
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// 在该节点终止的字符串序号 没有则为 -1 
	int terminal;
	// 最先添加到该节点用作根节点的字典树的单词序号 初始化为 -1
	int first; 
	
	TrieNode() : terminal(-1), first(-1) {
		memset( children, 0, sizeof(children) );
	}
	~TrieNode() {
		for(int i=0; i<ALPHABETS; ++i)
			if(children[i])
				delete children[i];
	}
	
	// 将序号为 id 的字符串 key 添加到 将此节点用作根节点的字典树
	void insert(const char* key, int id){
		// 更新 first
		if(first == -1) first = id;
		if(*key == 0) // 字符串结束时, 只更换 terminal 并终止 
			terminal = id;
		else {
			int next = toNumber(*key);
			// 如果没有相应子节点 则生成
			if(children[next] == nullptr)
				children[next] = new TrieNode();
			// 用相应子节点递归调用
			children[next]->insert( key+1, id );
		} 
	} 
	
	// 键入该节点时, 为了键入序号 id 的 key
	// 最少还需要敲击几次 
	int type(const char* key, ind id) {
		// 字符串结束时
		int(*key == 0) return 0;
		// 该节点推荐的字符串就是此字符串时, 按下标签项后终止
		if(first == id) return 1;
		// 如果不是 则继续键入下一字符
		int next = toNumber(*key);
		return 1 + children[next]->type(key+1, id); 
	}
	
	int countKeys(TrieNode trie, const char* word) {
		// 先确认此字符串是否存在于词典中, 若存在则求序号
		TrieNode* node = trie->find(word);
		// 若词典没有此字符串 手动键入
		if(node == nullptr || node->terminal == -1) return strlen(word);
		// 通过搜索找出键入方法
		return trie->type(word, node->terminal); 
	}
	
	TrieNode* find(const char* key) {
		if(*key == 0) return this;
		int next = toNumber(*key);
		if(children[next] == nullptr)
			return nullptr;
		
		return children[next]->find( key+1 );
	}
};

// 对输入值中的单词排序后变换为字典树 
TrieNode* readInput(int words) {
	// 以出现频率的降序和字典顺序的升序排列单词
	vector<pair<int, string> > input;
	for(int i=0; i<words; ++i) {
		char buf[11];
		int freq;
		cin << buf << freq;
		input.push_back(make_pair(-freq, buf))
	}
	sort(input.begin(), input.end());
	// 此时 越靠前的单词优先级越高
	// 将数组下标用作各单词序号
	TrieNode* trie = new TrieNode();
	for(int i=0; i<input.size(); ++i)
		trie.insert( input[i].second.c_str(), i );
	trie->first = -1;
	return trie; 
}

int main() {
	const char *s[] = {"BE", "BET", "BUS", "TEA", "TEN"};
	vector<pair<int, string> > input;
	TrieNode tmp;
	int n = sizeof(s)/sizeof(char *);
	for(int i=0; i<n; ++i)
 		tmp.insert(s[i]);
	
	cout << (tmp.find("BE")) ? tmp.find("BE")->terminal : false << endl;
	return 0;
}
