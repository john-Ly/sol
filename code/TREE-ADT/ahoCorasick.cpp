#include <iostream>
#include <vector>
#include <queue>
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
	int terminal;  // 在当前位置结束的字符串的序号
	
	// 失败连接: 在该节点中匹配失败时, 到此处继续操作
	// 既是对应于此节点的字符串的后缀 又是字典树中最长的字符串 
	TrieNode* fail;
	// 字符串输出目录: 访问该节点是发现的 缝衣针 字符串的序号
	vector<int> output;
	
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

// 给出字典树, 计算各节点的失败连接和字符串输出目录 
void computeFailFunc(TrieNode* root) {
	// 从根节点开始逐层计算各节点的失败连接
	queue<TrieNode*> q;
	// 根节点的失败连接是其本身
	root->fail = root;
	q.push(root);
	while(!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		// 计算 here 所有后代节点的失败连接并保存到队列
		for(int edge=0; edge<ALPHABETS; ++edge) {
			TrieNode* child = here->children[edge];
			if(!child) continue;
			// 第一层节点的失败连接总是根节点
			if(here == root)
				child->fail = root;
			else {
				// 如果不是 则沿着父节点的失败连接路径查找失败连接
				TrieNode* t = here->fail;
				while(t!=root && t->children[edge]==nullptr)  // 父子关系不明显 
					t = t->fail;
				if(t->children[edge]) t = t->children[edge];  // 父子关系明显确定
				// 但是 if 判断还是有必要 
				// 通过确认父节点 A 的失败连接 B 是否存在添加了 x的后代节点 Bx,
				// 就能判断 Bx 是 Ax 的失败连接 
				child->fail = t;
			} 
			
			// 字符串输出目录: 从跟踪失败连接的节点中复制后,
			// 该位置有终止的 "缝衣针" 字符串, 则添加
			child->output = child->fail->output;
			if(child->terminal != -1)
				child->output.pop_back(child->terminal);
			q.push(child); 
		}
	} 
}

vector<pair<int, int> > ahoCorasick(const string& s, TrieNode* root) {
	vector<pair<int, int> > ret;
	TrieNode* state = root;
	// 循环语句内部和 KMP 相同
	for(int i=0; i<s.size(); ++i) {
		int chr = toNumber(s[i]);
		while(state != root && state->children[chr] == nullptr)
			state = state->fail;
		if(state->children[chr])
			state = state->children[chr];
		for(int j=0; j<state->output.size(); ++j)
			ret.push_back(make_pair(i, state->output[j]));
	} 
	return ret;
}   

int main() {
	const char *s[] = {"BE", "BET", "BUS", "TEA", "TEN"};
	TrieNode tmp;
	int n = sizeof(s)/sizeof(char *);
	for(int i=0; i<n; ++i)
 		tmp.insert(s[i]);
	
	cout << (tmp.find("BE")) ? tmp.find("BE")->terminal : false << endl;
	return 0;
}
