#include <iostream>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4321292.html
// 双指针方法   一个负责小于指定数  另一个负责大于等于

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// partition list (满足条件的移动到前面)
// partition283
ListNode* partition(ListNode* head, int x) {
    if(!head) return nullptr;
    ListNode dummy {-1};
    dummy.next = head;
    ListNode* pre = &dummy;
    while(pre->next && pre->next->val < x)
        pre = pre->next;
    ListNode* cur = pre; // cur指向 >= x的前一个结点

    while (cur->next) {
        // 将小于的结点插入到pre之前  类似插入排序
        if(cur->next->val < x) {
            ListNode* t = cur->next;
            cur->next = t->next;
            t->next = pre->next;
            pre->next = t;
            pre = pre->next;
        } else {
            cur = cur->next;
        }
    }
    return dummy.next;
}

// 两个链表 然后在拼接
ListNode* parition(ListNode *head, int x) {
    if (!head) return nullptr;
    ListNode *dummy = new ListNode(-1);
    ListNode *newDummy = new ListNode(-1);
    dummy->next = head;
    ListNode *cur = dummy, *p = newDummy;
    while (cur->next) {
        if(cur->next->val < x) {
            p->next = cur->next;
            p = p->next;
            cur->next = cur->next->next;
            p->next = NULL;
        } else {
            cur = cur->next;
        }
    }
    p->next = dummy->next;
    return newDummy->next;
}
