// https://www.cnblogs.com/grandyang/p/5138936.html
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

//  Input: 2->1->3->5->6->4->7->NULL
// Output: 2->3->6->7->1->5->4->NULL
// 链表奇偶位置上分开 一次遍历即可(相对顺序不变)
ListNode* oddEvenList(ListNode* head) {
    // 空表或者只有一个节点
    if (!head || !head->next) return head;

    ListNode *odd = head, *even = head->next, *even_head = even;

    while (even && even->next) {
        odd = odd->next = even->next;
        even = even->next = odd->next;
    }
    //  指向odd链最后 一个点
    odd->next = even_head;
    return head;
}