#include <iostream>
using namespace std;

// 1. http://www.cnblogs.com/grandyang/p/4129891.html

// https://blog.csdn.net/qq_34840129/article/details/81092801
// 链表交换节点的思路非常清晰

// https://www.cnblogs.com/grandyang/p/4441680.html
// 递归做法  暂时理解不了

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// swap pair list
ListNode* swapPairs(ListNode* head) {
    ListNode dummy {-1};
    dummy.next = head;
    ListNode* pre = &dummy;

    while (pre->next && pre->next->next) {
        // pre指向 pair_node的前面
        ListNode *n1 = pre->next;
        ListNode *n2 = pre->next->next;

        pre->next = n2;
        n1->next = n2->next;
        n2->next = n1;

        pre = n1;
    }
    return dummy.next;
}