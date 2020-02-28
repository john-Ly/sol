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

ListNode* hasCycle(ListNode *head, int x) {

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
