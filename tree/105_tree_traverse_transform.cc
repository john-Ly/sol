#include<iostream>
#include<algorithm>  // equal
#include<vector>
#include<stack>
using namespace std;

template <class Comparable>
struct BinaryNode {
    Comparable data;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const Comparable& _data, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
        : data{ _data }, left{ lt }, right{ rt } { }

    BinaryNode( Comparable && _data, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr )
        : data{ std::move( _data ) }, left{ lt }, right{ rt } { }
};


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

// 递归函数中ps+1操作 可能会超出 栈溢出
// 终止条件: ps > pe; 直接返回 nullptr
template<class T>
BinaryNode<T>* buildTreeRecursive(const vector<T>& preorder, const vector<T>& inorder, int ps, int pe, int is, int ie) {
    if(ps > pe) return nullptr;
    BinaryNode<T>* node = new BinaryNode<T>(preorder[ps]);
    // 每一次递归都会遍历
    int pos;
    for(int i=is; i <= ie; i++) {
        if(inorder[i] == node->data) {
            pos = i;
            break;
        }
    }
    //                                                      po-is 就是左子树的个数
    node->left = buildTreeRecursive(preorder, inorder, ps+1, ps+(pos-is), is, pos-1);
    node->right = buildTreeRecursive(preorder, inorder, ps+(pos-is)+1, pe, pos+1, ie);
    return node;
}

template<class T>
BinaryNode<T>* buildTreeRecursive(const vector<T>& preorder, const vector<T>& inorder) {
    return buildTreeRecursive(preorder, inorder, 0, preorder.size()-1, 0, inorder.size()-1);
}


// First keep pushing the node from preorder to the stack until the top of stack is equal to the inorder's element, which means it comes to an end of the left node, and then flag it and pop until the top of the stack is not equal to the inorder (pop out the left and root), next step is to append the next node from preorder to the current node's right, and reset the flag, and iterate again until it finish iterating the preorder array.
// 前序和中序相同结果 说明树中所有节点都没有右孩子
template<class T>
BinaryNode<T>* buildTreeNonRecursive(const vector<T>& preorder, const vector<T>& inorder) {
    if(preorder.empty()) return nullptr;
    stack<BinaryNode<T>*> st;
    auto root = new BinaryNode<T>(preorder[0]);
    auto cur = root;
    // cur是按照前序遍历 总比preorder[i] 落后一个
    for(int i=1, j=0; i<preorder.size(); i++) {
        // 说明preorder 还没有遍历到 二叉树的最左节点
        if(cur->data != inorder[j]) {
            cur->left = new BinaryNode<T>(preorder[i]);
            st.push(cur);
            cur = cur->left;
        } else { // 前序cur == inorder 说明已经找到二叉树的最左边, 将下一个preorder[i] 当作右孩子: 是cur的右孩子 还是栈中节点的右孩子
            j++;
            // 栈里面维护的是 左子树(递归)
            while (!st.empty() && st.top()->data == inorder[j]) {
                cur = st.top(); st.pop();
                j++;
            }
            cur = cur->right = new BinaryNode<T>(preorder[i]);
        }
    }
    return root;
}

// https://www.cnblogs.com/grandyang/p/4296193.html
// @TODO 缺少递归版本
// postorder和preorder可以看成一个镜像问题
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/discuss/34555/The-iterative-solution-is-easier-than-you-think!/32916
template<class T>
BinaryNode<T>* buildTreeNonRecursive2(const vector<T>& postorder, const vector<T>& inorder) {
    if(postorder.empty()) return nullptr;
    stack<BinaryNode<T>*> st;
    auto root = new BinaryNode<T>(postorder.back());
    auto cur = root;
    // cur是按照前序遍历 总比preorder[i] 落后一个
    for(int i=postorder.size()-2, j=postorder.size()-1; i>=0; i--) {
        // 说明preorder 还没有遍历到 二叉树的最左节点
        if(cur->data != inorder[j]) {
            cur->right = new BinaryNode<T>(postorder[i]);
            st.push(cur);
            cur = cur->right;
        } else {
            j--;
            // 栈里面维护的是 左子树(递归)
            while (!st.empty() && st.top()->data == inorder[j]) {
                cur = st.top(); st.pop();
                j--;
            }
            cur = cur->left = new BinaryNode<T>(postorder[i]);
        }
    }
    return root;
}


template <class T>
void Preorder(BinaryNode<T> *root) {
    if(root == nullptr) return;

    cout << root->data << ' ';
    Preorder(root->left);     // Visit left subtree
    Preorder(root->right);    // Visit right subtree
}

template <class T>
void Postorder(BinaryNode<T> *root) {
    if(root == nullptr) return;

    Postorder(root->left);     // Visit left subtree
    Postorder(root->right);    // Visit right subtree
    cout << root->data << ' ';
}

template <class T>
void Inorder(BinaryNode<T> *root) {
    if(root == nullptr) return;

    Inorder(root->left);       //Visit left subtree
    cout << root->data << ' ';
    Inorder(root->right);      // Visit right subtree
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
    vector<int> preorder{27, 16, 9, 12, 10, 54, 36, 72};
    //                  L + 1 + R
    vector<int> inorder{9, 10, 12, 16, 27, 36, 54, 72};
    //                  L + R + 1
    vector<int> postorder{10, 12, 9, 16, 36, 72, 54, 27};
    vector<int> levelorder{27, 16, 54, 9, 36, 72, 12, 10};

    // for(auto i : slice(preorder, 1, 4) )
    //   	cout << i << " ";    // 16 9 12
    // cout << endl;
    // for(auto i : slice(inorder, 0, 3) )
    //   	cout << i << " ";    // 9 12 16
    // cout << endl;

    // for(auto i : postorder) cout << i << ' ';
    // cout << endl;
    // printPostOrder(preorder, inorder);
    // cout << endl;

    // for(auto i : preorder) cout << i << ' ';
    // cout << endl;
    // printPreOrder(postorder, inorder);
    // cout << endl;


    auto root = buildTreeNonRecursive2(postorder, inorder);
    cout << "in" << endl;
    Inorder(root);
    cout << endl;

    cout << "post" << endl;
    Postorder(root);
    cout << endl;
    Preorder(root);
    return 0;
}
