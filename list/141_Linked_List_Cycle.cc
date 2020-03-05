#include <iostream>
using namespace std;

// 如何做到时间复杂度为小于O(n)
// https://www.cnblogs.com/hiddenfox/p/3408931.html 详细的证明 @NOTE(一图胜千言)
// 1. 环的长度是多少
// 2. 环的起点
// 3. 将环的链表变成单链表

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


// https://www.cnblogs.com/grandyang/p/4137302.html#4197563
// Time O(n) + Space O(1)
// fast可能走了很多遍环 也可能1遍
// 为什么有环的情况下二者一定会相遇呢？
// 因为fast先进入环，在slow进入之后，如果把slow看作在前面，fast在后面每次循环都向slow靠近1，所以一定会相遇，而不会出现fast直接跳过slow的情况。

bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    // int lenCircle = 0;

    // 循环的次数 就是 环的长度
    while (fast && fast->next) {
        // lenCircle++;
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    // 第一次相遇后 停住fast 让slow走一圈即可  得到环长度
    return false;
}

// 如果存在环 返回环起点的下标(0-based); 否则返回 -1
// @TODO 一个数学公式, 但是好像右重复没有考虑
int detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    // 链表无环(fast指向了结尾)
    if (!fast || !fast->next) return -1;

    slow = head;
    ListNode* pre = nullptr;
    int pos = 0;
    while (slow != fast) {
        pos++;
        slow = slow->next;
        pre = fast;
        fast = fast->next;
    }

    // 断开环
    // pre->next = nullptr;
    return pos;
}