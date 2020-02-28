#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4249905.html
// O(n*logn)

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// merge两个有序链表
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

// 分治算法:将问题划分为相同规模的两个子问题
ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    // 利用快慢指针将链表分为两部分(pre用于将两个链表断开)
    ListNode *slow = head, *fast = head, *pre = nullptr;
    //     偶数(对半分)  奇数(后面多一个)
    while (fast && fast->next) {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = NULL;

    return merge(sortList(head), sortList(slow));
}