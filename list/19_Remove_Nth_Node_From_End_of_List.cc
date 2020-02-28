#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4606920.html

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
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

// 203. https://www.cnblogs.com/grandyang/p/4452252.html
ListNode* removeElements(ListNode* head, int n) {
    ListNode dummy = ListNode(-1);
    dummy.next = head;
    ListNode* pre = &dummy;

    while (pre->next) {
        if (pre->next->val == n) {
            auto t = pre->next;
            pre->next = t->next;
            delete t;
        } else {
            pre = pre->next;
        }
    }
    return dummy.next;
}

// 当判断下一个结点的值跟给定值相同的话，直接跳过下一个结点，将next指向下下一个结点，
// 而根本不断开下一个结点的next，更不用删除下一个结点了。
// 最后还要验证头结点是否需要删除，要的话直接返回下一个结点
ListNode* removeElements(ListNode* head, int val) {
    if (!head) return nullptr;
    auto cur = head;
    while (cur->next) {
        if (cur->next->val == val) cur->next = cur->next->next;
        else cur = cur->next;
    }
    return head->val == val ? head->next : head;
}

// 递归函数前: dfs
//       ..后: 回溯

// 可以采用分解问题的方法
ListNode* removeElements(ListNode* head, int val) {
    if (!head) return nullptr;
    head->next = removeElements(head->next, val);
    return head->val == val ? head->next : head;
}

int main() {
    return 0;
}
