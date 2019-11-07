#include <iostream>
#include <cstring> // memset()
using namespace std;

// 表示字典树节点的对象的声明方法 
// ================================================= 
// 保存英文大写字母 每个节点可能有 26 个后代节点
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// 表示字典树的一个节点的对象
struct TrieNode {
	TrieNode* children[ALPHABETS];
	bool terminal;  // 判断是否是终止节点
	
	TrieNode() : terminal(false) {
		memset( children, 0, sizeof(children) );
	}
	~TrieNode() {
		for(int i=0; i<ALPHABETS; ++i)
			if(children[i])
				delete children[i];
	}
	
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
			children[next]->insert( key+1 );
		} 
	} 
	
	TrieNode* find(const char* key) {
		if(*key == 0) return this;
		int next = toNumber(*key);
		if(children[next] == nullptr)
			return nullptr;
		
		return children[next]->find( key+1 );
	}

};

int main() {
	const char *s[] = {"BE", "BET", "BUS", "TEA", "TEN"};
	TrieNode tmp;
	int n = sizeof(s)/sizeof(char *);
	for(int i=0; i<n; ++i)
 		tmp.insert(s[i]);
	
	cout << (tmp.find("BE")) ? tmp.find("BE")->terminal : false << endl;
	return 0;
}
