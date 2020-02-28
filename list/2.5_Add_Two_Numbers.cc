// @TODO 大整数相加 (链表 逆序)
//
// Definition for singly-linked list.
#include <iostream>
#include <stack>
using namespace std;

// 1. http://www.cnblogs.com/grandyang/p/4129891.html
// @SEE 206_翻转链表
// https://www.cnblogs.com/grandyang/p/6216480.html


// 头插法 或者使用栈 或者递归 可以达到逆序的情况

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

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    stack<int> s1, s2;
    while (l1) {
        s1.push(l1->val);
        l1 = l1->next;
    }
    while (l2) {
        s2.push(l2->val);
        l2 = l2->next;
    }
    int sum = 0;
    ListNode *res = new ListNode(0);

    int extra = 0;
    while (!s1.empty() || !s2.empty()) {
        if (!s1.empty()) {sum += s1.top(); s1.pop();}
        if (!s2.empty()) {sum += s2.top(); s2.pop();}
        sum += extra;
        res->val = sum % 10;
        extra = sum/10;
        // 这个头插法 按照小端模式
        ListNode *head = new ListNode(extra);
        head->next = res;
        res = head;
    }
    //  1234   9500
    // + 453    500
    // -----   ----
    // 01687  10000

    return res->val == 0 ? res->next : res;
}


int main() {

    return 0;
}
