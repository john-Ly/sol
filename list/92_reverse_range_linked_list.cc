// https://leetcode.com/problems/reverse-linked-list-ii/solution/
// 翻转一个数组 可以借助两个指针(前后指针来做)
// 同样适用于链表(允许 链表的节点内容可以互换)
for (int i = 0, j = A.length - 1; i < j; i++, j--) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

#include <iostream>
using namespace std;

// 1. http://www.cnblogs.com/grandyang/p/4129891.html
// @SEE 206_翻转链表
// @TODO 递归做法不懂

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

ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode *dummy = new ListNode(-1), *pre = dummy;
    dummy->next = head;
    for (int i = 0; i < m - 1; ++i) pre = pre->next;
    ListNode *cur = pre->next;

    for (int i = m; i < n; ++i) {
        // 遍历结束后 cur_next指向了第三个节点
        // 临时变量是为了保存 第三个节点(毕竟两个节点就可以翻转)
        ListNode *t = cur->next;
        cur->next = t->next;
        // 头插法 可以生成逆序的链表
        t->next = pre->next;
        pre->next = t;
    }
    return dummy->next;
}


int main() {

    return 0;
}

