#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
	string label;
	TreeNode* parent;   // 指向父节点的指针
	vector<TreeNode*> children;  //指向后代节点的指针
};

void printLabels(TreeNode* root) {
	// 输出根节点中的数值
	cout << root->label << endl;
	// 递归输出将各个子节点用作根的子树包含的数值
	for(int i=0; i<root->children.size(); ++i)
		printLabels(root->children[i]);
}

int height(TreeNode* root) {
	int h = 0;
	for(int i=0; i<root->children.size(); ++i)
		h = max(h, 1+height(root->children[i]));
	return h;
}
