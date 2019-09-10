#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4066453.html
// 链表要注意 终止条件 + 开始条件(head==NULL 和 head->next == NULL)

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* deleteDuplicates(ListNode* head) {
    ListNode *cur = head;
    while (cur && cur->next) {
        // 第一个判断 会一直调到 不重复 节点为止
        if (cur->val == cur->next->val) {
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
    return head;
}
    
int main() {

    return 0;
}
