#include <algorithm>
#include <iostream> 
#include <vector> 
using namespace std;

// @TODO 解题的部分分成两个 

struct TreeNode {
	vector<TreeNode*> children;  //指向后代节点的指针 
};

// 保存已找出的最长 叶-叶路径的长度 
int longest; 

// 返回将 root 用作根节点的子树的高度 
int height(TreeNode* root) {
	vector<int> heights;
	for(int i=0; i<root->children.size(); ++i)
		heights.push_back(height(root->children[i]));
	// 没有子节点 返回0
	if(heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	
	// 考虑将 root 用作顶端节点的路径 
	if(heights.size() >= 2) {
		longest = max(longest, 2+heights[heights.size()-2]+heights[heights.size()-1]); 
	}
		
	return heights.back()+1;
}

int solve(TreeNode* root) {
	longest = 0;
	// 选择树高 和 最长叶-叶路径的长度  最大值
	int h = height(root);
	return max(longest, h); 
}
