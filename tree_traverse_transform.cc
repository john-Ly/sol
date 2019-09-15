#include<iostream>
#include<algorithm>  // equal
#include<vector>
using namespace std;


// @TODO
// 遍历顺序构建树
// 遍历顺序之间的转换

// @SEE equal two containers  std::equal(...)

vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>{v.begin()+a, v.begin()+b};
	// 拷贝构造 实际的元素为 v.begin()+a, v.begin()+b-1
	// 最后一个元素的下标是上界(无法达到)
}

void printPostOrder(const vector<int>& preorder, const vector<int>& inorder){
	const int N = preorder.size();
	// 初始部分:是空树则立即终止
	if(preorder.empty()) return;
	// 前序遍历 -- 树的根节点
	const int root = preorder.front();
	// 从中序遍历找出根节点后, 可以求出左侧子树的大小
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	// 右侧子树的大小
	const int R = N - L - 1;
	// 输出左侧和右侧子树的遍历结果
	printPostOrder(slice(preorder, 1, L+1), slice(inorder, 0, L));  // 左闭右开区间: 方便计算区间长度
	printPostOrder(slice(preorder, L+1, N), slice(inorder, L+1, N));

	// 后序遍历 最后输出根节点
	cout << root << " ";
}

void printPreOrder(const vector<int>& postorder, const vector<int>& inorder){
	const int N = postorder.size();
	// 初始部分:是空树则立即终止
	if(postorder.empty()) return;
	// 前序遍历 -- 树的根节点
	const int root = postorder.back();
	// 从中序遍历找出根节点后, 可以求出左侧子树的大小
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	// 右侧子树的大小
	const int R = N - L - 1;

	// 前序遍历 最后输出根节点
	cout << root << " ";
	// 输出左侧和右侧子树的遍历结果
	printPreOrder(slice(postorder, 0, L), slice(inorder, 0, L));  // 左闭右开区间: 方便计算区间长度
	printPreOrder(slice(postorder, L, N-1), slice(inorder, L+1, N));
}

int main() {
	/* BST
	            27
			   /  \
			  16   54
			 /    /  \
			9    36  72
             \
              12
    */

    //                  1 + L + R
	vector<int> preorder{27, 16, 9, 12, 54, 36, 72};
    //                  L + 1 + R
	vector<int> inorder{9, 12, 16, 27, 36, 54, 72};
    //                  L + R + 1
	vector<int> postorder{12, 9, 16, 36, 72, 54, 27};
	vector<int> levelorder{27, 16, 54, 9, 36, 72, 12};

	// for(auto i : slice(preorder, 1, 4) )
    //   	cout << i << " ";    // 16 9 12
    // cout << endl;
	// for(auto i : slice(inorder, 0, 3) )
    //   	cout << i << " ";    // 9 12 16
    // cout << endl;

    for(auto i : postorder) cout << i << ' ';
    cout << endl;
	printPostOrder(preorder, inorder);
    cout << endl;

    for(auto i : preorder) cout << i << ' ';
    cout << endl;
	printPreOrder(postorder, inorder);
    cout << endl;
	return 0;
}
