#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 大整数相加
namespace sol_2 {
// http://www.cnblogs.com/grandyang/p/4129891.html
// 接收的链表的低位放第一个节点(逆序成)小端模式)
// (2 -> 4 -> 3) : 342
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // 附加头节点 可以统一处理(如果两个结点全部为空)
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


// https://www.cnblogs.com/grandyang/p/6216480.html
// 头插法 或者使用栈 或者递归 可以达到逆序的情况
ListNode* addTwoNumbers_bigEndian(ListNode* l1, ListNode* l2) {
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

}

// 反转单链表
namespace sol_206 {
// ListNode dummy {-1};
// while (head) {
//     auto next = head->next;
//     head->next = dummy.next;
//     dummy.next = head;
//     head = next;
// }
// return dummy.next;
ListNode* reverseList(ListNode* head) {
    ListNode *newHead = NULL;
    while (head) {
        ListNode *t = head->next;
        // 头插法
        head->next = newHead;  // 先处理老的头节点
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
ListNode* reverseList_recursive(ListNode* head) {
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
}

namespace sol_92 {
// https://leetcode.com/problems/reverse-linked-list-ii/solution/
//  Input: 1->2->3->4->5->NULL, m = 2, n = 4
// Output: 1->4->3->2->5->NULL
// 不是常规逻辑的反转, 可能反转部分(链变被分为三个部分)
ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode dummy {-1};
    dummy.next = head;
    ListNode* pre = &dummy;

    for (int i = 0; i < m - 1; ++i) pre = pre->next;
    auto cur = pre->next;

    // 相当于变换三个结点( 1-> 2 -> 3  :  2要接管3后面的结点)
    for (int i = m; i < n; ++i) {
        // 遍历结束后 cur_next指向了第三个节点
        auto t = cur->next;
        cur->next = t->next;
        // 头插法 可以生成逆序的链表
        t->next = pre->next;

        pre->next = t;
    }
    return dummy.next;
}

}
