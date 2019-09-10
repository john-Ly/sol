#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// https://leetcode.com/problems/reverse-nodes-in-k-group/discuss/11440/Non-recursive-Java-solution-and-idea
/**
    * Reverse a link list between begin and end exclusively
    * an example:
    * a linked list:
    * 0->1->2->3->4->5->6
    * |           |
    * begin       end
    * after call begin = reverse(begin, end)
    *
    * 0->3->2->1->4->5->6
    *          |  |
    *      begin end
    * @return the reversed list's 'begin' node, which is the precedence of node end
*/

ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || head->next==nullptr || k == 1) return head;
    ListNode *dummy = new ListNode(-1), *pre = dummy, *cur = head;
    dummy->next = head;
    for (int i = 1; cur; ++i) {
        if (i % k == 0) {
            pre = reverseRange(pre, cur->next);
            cur = pre->next;
        } else {
            cur = cur->next;
        }
    }
    return dummy->next;
}

// both open (begin, end)
ListNode* reverseRange(ListNode* begin, ListNode* end) {
    ListNode *cur = begin->next;
    ListNode *first = cur;
    ListNode *prev = begin;

    // 头插法
    ListNode *next=nullptr;
    while (cur!=end){
        next = cur->next;
        cur->next = prev->next;
        prev->next = cur;
        cur = next;
    }

    first->next = end;
    return first;
}