#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4250107.html
// 插入排序

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* insertionSortList(ListNode* head) {
    ListNode *dummy = new ListNode(-1), *cur = dummy;
    while (head) {
        ListNode* t = head->next;

        cur = dummy;
        while(cur->next && cur->next->val < head->val) {
            cur = cur->next;
        }

        // cur为当前插入位置的前一个节点(cur最想最后一个小于head->val的节点)
        head->next = cur-next;
        cur->next = head;

        head = t;
    }
    return dummy->next;
}

