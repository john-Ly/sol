#include <algorithm>
#include <iostream> 
#include <vector> 
using namespace std;

// @TODO ����Ĳ��ֳַ����� 

struct TreeNode {
	vector<TreeNode*> children;  //ָ�����ڵ��ָ�� 
};

// �������ҳ���� Ҷ-Ҷ·���ĳ��� 
int longest; 

// ���ؽ� root �������ڵ�������ĸ߶� 
int height(TreeNode* root) {
	vector<int> heights;
	for(int i=0; i<root->children.size(); ++i)
		heights.push_back(height(root->children[i]));
	// û���ӽڵ� ����0
	if(heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	
	// ���ǽ� root �������˽ڵ��·�� 
	if(heights.size() >= 2) {
		longest = max(longest, 2+heights[heights.size()-2]+heights[heights.size()-1]); 
	}
		
	return heights.back()+1;
}

int solve(TreeNode* root) {
	longest = 0;
	// ѡ������ �� �Ҷ-Ҷ·���ĳ���  ���ֵ
	int h = height(root);
	return max(longest, h); 
}
