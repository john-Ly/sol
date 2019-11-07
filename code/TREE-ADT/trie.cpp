#include <iostream>
#include <cstring> // memset()
using namespace std;

// ��ʾ�ֵ����ڵ�Ķ������������ 
// ================================================= 
// ����Ӣ�Ĵ�д��ĸ ÿ���ڵ������ 26 ������ڵ�
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

// ��ʾ�ֵ�����һ���ڵ�Ķ���
struct TrieNode {
	TrieNode* children[ALPHABETS];
	bool terminal;  // �ж��Ƿ�����ֹ�ڵ�
	
	TrieNode() : terminal(false) {
		memset( children, 0, sizeof(children) );
	}
	~TrieNode() {
		for(int i=0; i<ALPHABETS; ++i)
			if(children[i])
				delete children[i];
	}
	
	// �򽫴˽ڵ��������ڵ���ֵ��� ����ַ��� key 
	void insert(const char* key){
		// �ַ���������Ϻ� �� terminal ����ֵ������
		if(*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			// ���û����Ӧ�ӽڵ� ������
			if(children[next] == nullptr)
				children[next] = new TrieNode();
			// ����Ӧ�ӽڵ�ݹ����
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
