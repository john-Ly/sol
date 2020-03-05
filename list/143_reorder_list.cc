#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 1->2->3->4, reorder 1->4->2->3.
// 1->2->3->4->5, reorder 1->5->2->4->3.

// 双指针找中间结点
// a. 如果要断开两个结点
//     while (fast->next && fast->next->next)
//   最后直接断开 slow->next                ----> slow是中点的前驱
//
// ListNode *fast = head, *slow = head;
// while (fast->next && fast->next->next) {
//     slow = slow->next;
//     fast = fast->next->next;
// }
// // 1. 奇数个点: fast指向倒数第一个点
// // 2. 偶数: fast指向倒数第二个点
// ListNode *mid = slow->next;
// slow->next = nullptr点
//
// b. 不断开两个结点
//     while (fast && fast->next)
//   slow指向中间结点 fast可能会指向nullptr(偶数) + 最后一个(奇数)

// https://www.cnblogs.com/grandyang/p/4254860.html
void reorderList(ListNode* head) {
    //  只有两个节点的情况
    if (!head || !head->next || !head->next->next) return;

    // a. 中间断开 后半段少
    ListNode *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 1. 奇数个点: fast指向倒数第一个点
    // 2. 偶数: fast指向倒数第二个点
    ListNode *mid = slow->next;
    slow->next = nullptr;

    // 无头结点头插法 pre代表翻转后的第一个节点
    ListNode *last = mid, *pre = nullptr;
    while(last) {
        ListNode * next = last->next;
        last->next = pre;
        pre = last;
        last = next;
    }

    // 两个链变 交替插入(画图)
    while(head && pre) {
        ListNode* next = head->next;

        head->next = pre;
        pre = pre->next;
        head->next->next = next;

        head = next;
    }
    // 总结点奇数  n_pre + 1 = n_head
    // 总结点偶数  n_pre = n_head
    // 所以循环后 一定完成链表的插入
}