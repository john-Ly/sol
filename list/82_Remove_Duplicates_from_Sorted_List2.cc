#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4069003.html
// 链表要注意
// 1. 终止条件 + 开始条件(head==NULL 和 head->next == NULL)
// 2. 链表每次访问的时候 要确认节点是否是NULL(如果在循环的条件里还好)

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* deleteDuplicates(ListNode* head) {
    ListNode *dummy = new ListNode(-1), *pre = &preHead;
    pre->next = head;

    while (pre->next) {
        ListNode *cur = pre->next;
        // cur 在循环后指向 重复节点的最后一位
        while (cur->next && cur->val == cur->next->val) {
            cur = cur->next;
        }

        if (cur == pre->next) pre = pre->next;
        else pre->next = cur->next;
    }
    return dummy->next;
}

int main() {

    return 0;
}
