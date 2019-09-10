#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4606920.html

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 实际上维护领一个窗口  十分巧妙
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(!head) return NULL;
    ListNode *pre = head, *cur = head;
    // 题目说明n始终有效, 直接cur=cur->next;
    for(int i=0; i<n; i++) cur = cur->next;
    if(!cur) return pre->next;
    while(cur->next) {
        cur = cur->next;
        pre = pre->next;
    }

    pre->next = pre->next->next;
    return head;
}

ListNode* removeNthFromEnd2(ListNode* head, int n) {
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    int len = 0;
    ListNode *p = head;
    while(p) {
        len++;
        p = p->next;
    }

    len -= n;   // 倒数第n个, 正数..
    p = dummy;  // 删除结点需要知道待删结点的 前驱结点
    while(len>0) {
        len--;
        p = p->next;
    }
    p->next = p->next->next;
    return dummy->next;
}


int main() {
    return 0;
}
