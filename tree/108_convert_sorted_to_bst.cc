#include <vector>
#include <algorithm>
#include <climit>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4298069.html
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 有序数组转换为BST
// https://www.cnblogs.com/grandyang/p/4295245.html
class sol_108 {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
      return helper(nums, 0 , nums.size());
    }

    TreeNode* helper(vector<int>& nums, size_t left, size_t right) {
      if (left >= right) return nullptr;
      int mid = left + (right - left) / 2;
      TreeNode *cur = new TreeNode(nums[mid]);
      cur->left = helper(nums, left, mid);
      cur->right = helper(nums, mid + 1, right);
      return cur;
    }
};

// 有序数组转换为BST
// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/solution/
class sol_109 {
public:
TreeNode* sortedListToBST(TreeNode<T>* head) {
    if (!head) return nullptr;  // 无节点
    if (!head->next) return new TreeNode{head->val}; // 一个节点

    // 1. 快慢指针找到中点
    auto fast = head, slow = head;
    auto last = slow;
    while(fast->next && fast->next->next) {
        last = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // 断开链表 不包含slow指向的结点
    fast = slow->next;
    last->next = nullptr;
    TreeNode * root = new TreeNode<T>(slow->val);

    // 如果只有两个结点的情况
    if(slow != head) {
        root->left = sortedListToBST(head);
    }

    root->right = sortedListToBST(fast);
    return root;
}
};

// https://www.cnblogs.com/grandyang/p/9615871.html
// BST转化为 循环双向链表(有序) 返回最小结点
class sol_426 {
public:
    TreeNode* treeToDoublyList(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode *head = nullptr, *pre = nullptr;
        stack<TreeNode*> st;
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            root = st.top(); st.pop();

            if (!head) head = root;
            if (pre) {
                pre->right = root;
                root->left = pre;
            }
            pre = root;

            root = root->right;
        }
        // 循环退出后 pre指向最后一个结点 环
        head->left = pre;
        pre->right = head;
        return head;
    }
};