#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    explicit Node(int _val) : val(_val), next(nullptr) {}
};


// 27: https://www.cnblogs.com/grandyang/p/4606700.html
int removeElement(vector<int>& nums, int val) {
    // res相当于新的下标
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != val) nums[res++] = nums[i];
    }
    return res;
}

// https://www.cnblogs.com/grandyang/p/4647576.html
// 给出要删除节点的指针(拷贝值 删除下一个节点)
void deleteNode(Node* node) {
    node->val = node->next->val;
    Node *tmp = node->next;
    node->next = tmp->next;
    delete tmp;
}

// 203: remove linked list elements @19