#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4128461.html

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return NULL;
    int lenA = getLength(headA), lenB = getLength(headB);
    if (lenA < lenB) {
        for (int i = 0; i < lenB - lenA; ++i) headB = headB->next;
    } else {
        for (int i = 0; i < lenA - lenB; ++i) headA = headA->next;
    }

    while (headA && headB && headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    return (headA && headB) ? headA : NULL;
}

int getLength(ListNode* head) {
    int cnt = 0;
    while (head) {
        ++cnt;
        head = head->next;
    }
    return cnt;
}

// 无论是否有交点 都可以假设相交(NULL也可以看成共同的交点)
// 保证长链表跟短链表  相同成长度处遍历即可
ListNode *getIntersectionNode1(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return NULL;
    ListNode *a = headA, *b = headB;
    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}

int main() {
    cout << addDigits(38) << endl;
    return 0;
}