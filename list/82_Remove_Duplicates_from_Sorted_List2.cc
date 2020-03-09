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

// 有序 去除重复(保留)
//  Input: 1->1->2->3->3
// Output: 1->2->3
ListNode* deleteDuplicates_wi(ListNode* head) {
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

// 有序 去除重复(不保留)
//  Input: 1->1->2->3->3
// Output: 2->3
// 可能删除头节点 需要dummy
ListNode* deleteDuplicates_wo(ListNode* head) {
    // 至少两个结点存在(否则没有重复)
    if (!head || !head->next) return head;
    ListNode dummy {-1}, *pre = &dummy;
    dummy.next = head;

    while (pre->next) {
        // 判断 当前节点是重复节点
        ListNode *cur = pre->next;
        // cur 在循环后指向 重复节点的最后一位
        while (cur->next && cur->val == cur->next->val) {
            cur = cur->next;
        }

        if (cur == pre->next) pre = pre->next;
        else {
            while(pre->next != cur->next) {
                auto old = pre->next;
                pre->next = old->next;
                delete old;
            }
            // 退出循环后
            pre->next = cur->next;
        }
    }
    return dummy.next;
}