#include <iostream>
#include <iostream>
using namespace std;

// @TODO 如何做到时间复杂度为小于O(n)
// https://www.cnblogs.com/hiddenfox/p/3408931.html 详细的证明 @NOTE(一图胜千言)
// 1. 环的长度是多少
// 2. 环的起点
// 3. 将环的链表变成单链表
// 4. 如何判断两个单链表是否有交点?如何找到第一个相较的点?

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 为什么有环的情况下二者一定会相遇呢？
// 因为fast先进入环，在slow进入之后，如果把slow看作在前面，fast在后面每次循环都向slow靠近1，所以一定会相遇，而不会出现fast直接跳过slow的情况。

// 时间复杂度 O(n)
// 空间复杂度 O(1)
bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    int lenCircle = 0;
    // 循环的次数 就是 环的长度
    while (fast && fast->next) {
        lenCircle++;
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// 如果存在环 返回环起点的下标(0-based); 否则返回 -1
int detectCycle(ListNode *head) {
    int pos = 0;
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    // 链表无环
    if (!fast || !fast->next) return -1;

    slow = head;
    while (slow != fast) {
        pos++;
        slow = slow->next;
        fast = fast->next;
    }
    return pos;
}