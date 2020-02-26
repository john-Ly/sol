#include <iostream>
using namespace std;

// 1. http://www.cnblogs.com/grandyang/p/4129891.html

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 接收的链表的低位放第一个节点(小端模式)
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // 附加头节点 主要是删除和插入节点  可以统一处理@TODO
    ListNode preHead(0), *p = &preHead;
    int extra = 0;
    // 两个链表全部为空的时候，如果进位标志为1再次进入循环 最后一个节点的值为1
    while (l1 || l2 || extra) {
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + extra;
        extra = sum / 10;
        p->next = new ListNode(sum % 10);
        p = p->next;
        l1 = l1 ? l1->next : l1;
        l2 = l2 ? l2->next : l2;
    }
    return preHead.next;
}

// 反转单链表
ListNode* reverseList(ListNode* head) {
    ListNode *newHead = NULL;
    while (head) {
        ListNode *t = head->next;
        // 还是头插法 没有附加头节点
        head->next = newHead;  // 先处理老结点
        newHead = head;        // 更新当前结点
        head = t;
    }
    return newHead;
}

// https://leetcode.com/problems/reverse-linked-list/solution/
// Be very careful that n1's next must point to Ø.
// If you forget about this, your linked list has a cycle in it.
// This bug could be caught if you test your code with a linked list of size 2.
//
// 子问题分析真的很绕 @TODO
ListNode* reverseList(ListNode* head) {
    if (!head || !(head -> next)) {
        return head;
    }
    ListNode* node = reverseList(head -> next);
    // node 返回逆序后的一个头节点(但是链表的最后一个节点还和head有关系)
    // 交换两个节点==最简单的逆序
    head -> next -> next = head;
    head -> next = NULL;

    return node;
}

int main() {

    return 0;
}
