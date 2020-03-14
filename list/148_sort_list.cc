#include <iostream>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4606710.html
// 分治法 把k个链表 分成两份 k/2个sorted lists

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

namespace sol_merge_k_sorted {
// merge(l1, l2) = 返回排序后的链表
// 子问题
ListNode* mergeTwoLists_recu(ListNode* l1, ListNode* l2) {
    // 错误处理
    if (!l1) return l2; if (!l2) return l1;
    // 假设只有两个节点 剩下的节点归类到子问题
    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

// merge两个有序链表
ListNode* mergeTwoLists_iter(ListNode* l1, ListNode* l2) {
    ListNode dummy {-1}, *cur = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy.next;
}
}

// https://www.cnblogs.com/grandyang/p/4249905.html
// O(n*logn)
ListNode* mergesortList(ListNode* head) {
    if (!head || !head->next) return head;
    // 利用快慢指针将链表分为两部分(pre用于将两个链表断开)
    ListNode *slow = head, *fast = head, *pre = nullptr;
    //     偶数(对半分)  奇数(后面多一个)
    while (fast && fast->next) {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = NULL;

    return sol_merge_k_sorted::mergeTwoLists_iter(mergesortList(head), mergesortList(slow));
}

// https://www.cnblogs.com/grandyang/p/4250107.html
// 插入排序
ListNode* insertionSortList(ListNode* head) {
    ListNode dummy {-1}, *cur = nullptr;
    while (head) {
        ListNode* t = head->next;

        // 每次从前半区(有序) 查找插入位置(pre)
        cur = &dummy;
        while(cur->next && cur->next->val < head->val) {
            cur = cur->next;
        }
        head->next = cur-next;
        cur->next = head;

        head = t;
    }
    return dummy.next;
}

namespace sol_88 {
// https://www.cnblogs.com/grandyang/p/4059650.html

// 两个有序数组 merge
// m, n : 两个数组初始化时元素的个数
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    // 可能i也有剩余 不过是放在nums1数组中 所以可以不考虑
    while (j >= 0) nums1[k--] = nums2[j--];
}

}