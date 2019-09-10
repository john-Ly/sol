#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4086297.html

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode *dummy = new ListNode(-1), *cur = dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy->next;
}


// merge(l1, l2) = 返回排序后的链表
// 子问题
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    // 错误处理
    if (!l1) return l2; if (!l2) return l1;
    // 假设只有两个节点 剩下的节点归类到子问题
    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

int main() {

    return 0;
}