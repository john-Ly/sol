#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// @TODO 不带头节点的头插法
void reorderList(ListNode* head) {
    // 只有两个节点的情况
    if (!head || !head->next || !head->next->next) return;
    ListNode *fast = head, *slow = head;
    //     1. 奇数个节点   2. 偶数个节点
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 1. 奇数个点: fast指向倒数第一个点
    // 2. 偶数: fast指向倒数第二个点
    ListNode *mid = slow->next;
    slow->next = NULL;
    // pre 一直指向第一个节点
    ListNode *last = mid, *pre = NULL;
    while(last) {
        ListNode * next = last->next;
        last->next = pre;
        pre = last;
        last = next;
    }
    while(head && pre) {
        ListNode * next = head->next;
        head->next = pre;
        pre = pre->next;
        head->next->next = next;
        head = next;
    }
    // 总结点奇数  n_pre + 1 = n_head
    // 总结点偶数  n_pre = n_head
    // 所以循环后 一定完成链表的插入
}

ListNode* reverseList(ListNode* head) {
    ListNode *newHead = NULL;
    while (head) {
        ListNode *t = head->next;
        // 还是头插法 没有附加头节点
        head->next = newHead;
        newHead = head;
        head = t;
    }
    return newHead;
}

int main() {

    return 0;
}
