#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	// ���� KMP �ҳ��Լ����� 
	// �� N ���ҳ� N   begin=0ʱ���ҵ��Լ�����, ����begin���ܵ��� 0
	int begin = 1, matched = 0;
	// ��Ҫ�Ƚϵ��ַ����� N �����һ��λ��ǰһֱ����, ����¼����ƥ�� 
	while(begin + matched < m) {
		if(N[begin + matched] == N[matched]) {
			++matched;
			pi[begin+matched-1] = matched;
		} else {
			// �쳣: matched ����0ʱ, ����һ��λ�ÿ�ʼ�����Ƚ�
			if(matched == 0)
				++begin;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return pi;
}

// ���� KMP �ı��� 
// ���ؼ��� S ǰ׺���� S` ��׺���ַ�������󳤶�
// maxOverlap S <--reverse--> S'  
int maxOverlap(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	
	// �� begin =matched =0 ��ʼ
	int begin = 0, matched = 0;
	// ���� 0 �� |S|-1 ֮�������λ�� 
	while(begin < n) {
		if(matched < m && a[begin + matched] == b[matched]) {
			++matched;
			// �ҳ���һ�� 
			if(begin+matched == n)
				return matched;
		} else {
			if(matched == 0)
				++begin;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return 0;
}

int main() {
    string haystack = "anon";
    // std::reverse(std::begin(s), std::end(s));
    string needle = "nona";
    cout << maxOverlap(haystack, needle) << " ";

	return 0;
}
