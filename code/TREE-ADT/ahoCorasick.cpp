#include <iostream>
#include <vector>
#include <queue>
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
	int terminal;  // �ڵ�ǰλ�ý������ַ��������
	
	// ʧ������: �ڸýڵ���ƥ��ʧ��ʱ, ���˴���������
	// ���Ƕ�Ӧ�ڴ˽ڵ���ַ����ĺ�׺ �����ֵ���������ַ��� 
	TrieNode* fail;
	// �ַ������Ŀ¼: ���ʸýڵ��Ƿ��ֵ� ������ �ַ��������
	vector<int> output;
	
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

// �����ֵ���, ������ڵ��ʧ�����Ӻ��ַ������Ŀ¼ 
void computeFailFunc(TrieNode* root) {
	// �Ӹ��ڵ㿪ʼ��������ڵ��ʧ������
	queue<TrieNode*> q;
	// ���ڵ��ʧ���������䱾��
	root->fail = root;
	q.push(root);
	while(!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		// ���� here ���к���ڵ��ʧ�����Ӳ����浽����
		for(int edge=0; edge<ALPHABETS; ++edge) {
			TrieNode* child = here->children[edge];
			if(!child) continue;
			// ��һ��ڵ��ʧ���������Ǹ��ڵ�
			if(here == root)
				child->fail = root;
			else {
				// ������� �����Ÿ��ڵ��ʧ������·������ʧ������
				TrieNode* t = here->fail;
				while(t!=root && t->children[edge]==nullptr)  // ���ӹ�ϵ������ 
					t = t->fail;
				if(t->children[edge]) t = t->children[edge];  // ���ӹ�ϵ����ȷ��
				// ���� if �жϻ����б�Ҫ 
				// ͨ��ȷ�ϸ��ڵ� A ��ʧ������ B �Ƿ��������� x�ĺ���ڵ� Bx,
				// �����ж� Bx �� Ax ��ʧ������ 
				child->fail = t;
			} 
			
			// �ַ������Ŀ¼: �Ӹ���ʧ�����ӵĽڵ��и��ƺ�,
			// ��λ������ֹ�� "������" �ַ���, �����
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
	// ѭ������ڲ��� KMP ��ͬ
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
