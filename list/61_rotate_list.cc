#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// @SEE 19 先找到倒数第k个结点 然后处理
//  Given 1->2->3->4->5->NULL and k = 2,
// return 4->5->1->2->3->NULL.

// rotate list61
// 链变形成环十分方便 所以rotate 简单
ListNode *rotateRight(ListNode *head, int k) {
    if (!head) return NULL;
    int n = 1;
    ListNode *cur = head;
    while (cur->next) {
        ++n;
        cur = cur->next;
    }
    // 遍历到list的尾节点(同时统计了节点的个数)
    // 向右旋转k === 相当于 向左旋转 n- k%n

    cur->next = head;
    int m = n - k % n;
    for (int i = 0; i < m; ++i) {
        cur = cur->next;
    }
    // cur下一个位置指向 rotate之后的头节点

    ListNode *newhead = cur->next;
    cur->next = NULL;
    return newhead;
}

// 快慢指针
ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return nullptr;
        int n = 0;
        ListNode *cur = head;
        while (cur) {
            ++n;
            cur = cur->next;
        }
        k %= n;

        // 1. 快指针先走k步
        ListNode *fast = head, *slow = head;
        for (int i = 0; i < k; ++i) {
            if (fast) fast = fast->next;
        }

        // 慢指针下一个位置指向 rotate之后的头节点
        if(!fast) return head;
        while(fast->next) {
            fast = fast->next;
            slow = slow->next;
        }

        fast->next = head;
        fast = slow->next;
        slow->next = NULL;

        return fast;
}