#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4128461.html

// 4. 如何判断两个无环单链表是否有交点?如何找到第一个相交的点
//    时间复杂度为O(M+N) 额外空间复杂度O(1)
//  思路a: 使用hash表
//      先遍历一个链表 记录hash<ListNode*> 再遍历第二个链表有重复即为第一个交点
//  思路b: 遍历
//      遍历两个链表 统计各自的长度len1 len2
//      长链表先走abs(len1-len2), 然后两个链表同步走 相交再相同的点
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 判断两个链表的交点(无环链表)
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