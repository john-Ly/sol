// @TODO 大整数相加 (链表 逆序)
//  如果链表存放的位置是小端顺序  建议先做成大端(因为大端意味着 低位放在链表头部 方便计算)
//  @NOTE 链表翻转很重要
//
#include <iostream>
#include <iostream>
using namespace std;

// http://www.cnblogs.com/grandyang/p/4129891.html

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

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


int main() {

    return 0;
}
