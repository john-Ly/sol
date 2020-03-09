#include <iostream>

ListNode* temp;
bool isPalindrome(ListNode* head) {
    temp = head;
    return check(head);
}

bool check(ListNode* p) {
    if (nullptr == p) return true;
    bool isPal = check(p->next) & (temp->val == p->val);
    temp = temp->next;
    return isPal;
}

// 回文
bool isPalindrome(ListNode* head) {
    // 只有0/1个节点的情况
    if (!head || !head->next) return true;
    ListNode *fast = head, *slow = head;
    //     1. 奇数个节点   2. 偶数个节点
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 1. 奇数个点: fast指向倒数第一个点
    // 2. 偶数: fast指向倒数第二个点
    ListNode *mid = slow->next;
    // last 一直指向第一个节点 (翻转后半段) // last现在是一个空链表 采用头插法
    ListNode *last = NULL;
    while(mid) {
        ListNode * next = mid->next;
        mid->next = last;
        last = mid;
        mid = next;
    }

    ListNode *p = head;
    while(last) {
        if(last->val != p->val) return false;
        last = last->next;
        p = p->next;
    }

    return true;
}
