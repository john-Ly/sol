#include <iostream>
#include <cstring> // memset()
using namespace std;

/*
//#include <cstring>
const char str[] = "How many characters does this string contain?";

std::cout << "without null character: " << std::strlen(str) << '\n'
         << "with null character: " << sizeof str << '\n';
*/

// ��ʾ�ֵ����ڵ�Ķ������������ 
// ================================================= 
// ����Ӣ�Ĵ�д��ĸ ÿ���ڵ������ 26 ������ڵ�
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// ��ʾ�ֵ�����һ���ڵ�Ķ���
struct TrieNode {
	TrieNode* children[ALPHABETS];
	// �ڸýڵ���ֹ���ַ������ û����Ϊ -1 
	int terminal;
	// ������ӵ��ýڵ��������ڵ���ֵ����ĵ������ ��ʼ��Ϊ -1
	int first; 
	
	TrieNode() : terminal(-1), first(-1) {
		memset( children, 0, sizeof(children) );
	}
	~TrieNode() {
		for(int i=0; i<ALPHABETS; ++i)
			if(children[i])
				delete children[i];
	}
	
	// �����Ϊ id ���ַ��� key ��ӵ� ���˽ڵ��������ڵ���ֵ���
	void insert(const char* key, int id){
		// ���� first
		if(first == -1) first = id;
		if(*key == 0) // �ַ�������ʱ, ֻ���� terminal ����ֹ 
			terminal = id;
		else {
			int next = toNumber(*key);
			// ���û����Ӧ�ӽڵ� ������
			if(children[next] == nullptr)
				children[next] = new TrieNode();
			// ����Ӧ�ӽڵ�ݹ����
			children[next]->insert( key+1, id );
		} 
	} 
	
	// ����ýڵ�ʱ, Ϊ�˼������ id �� key
	// ���ٻ���Ҫ�û����� 
	int type(const char* key, ind id) {
		// �ַ�������ʱ
		int(*key == 0) return 0;
		// �ýڵ��Ƽ����ַ������Ǵ��ַ���ʱ, ���±�ǩ�����ֹ
		if(first == id) return 1;
		// ������� �����������һ�ַ�
		int next = toNumber(*key);
		return 1 + children[next]->type(key+1, id); 
	}
	
	int countKeys(TrieNode trie, const char* word) {
		// ��ȷ�ϴ��ַ����Ƿ�����ڴʵ���, �������������
		TrieNode* node = trie->find(word);
		// ���ʵ�û�д��ַ��� �ֶ�����
		if(node == nullptr || node->terminal == -1) return strlen(word);
		// ͨ�������ҳ����뷽��
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

// ������ֵ�еĵ��������任Ϊ�ֵ��� 
TrieNode* readInput(int words) {
	// �Գ���Ƶ�ʵĽ�����ֵ�˳����������е���
	vector<pair<int, string> > input;
	for(int i=0; i<words; ++i) {
		char buf[11];
		int freq;
		cin << buf << freq;
		input.push_back(make_pair(-freq, buf))
	}
	sort(input.begin(), input.end());
	// ��ʱ Խ��ǰ�ĵ������ȼ�Խ��
	// �������±��������������
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
