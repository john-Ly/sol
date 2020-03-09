#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

/*
 如何找到随机指针(指向的是原链表中的任何一个节点 也就是新链表值是不同的)
 利用hash 确定位置的映射

 @TODO 如果链表有环 怎么处理
 */

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        auto res = new Node(head->val, nullptr, nullptr);
        auto cur = head->next;
        auto cur2 = res;
        unordered_map<Node*, Node*> node_map;
        node_map[head] = res;  //@TODO 这里是关键点 应该存储 src和dest的原始映射
        node_map[nullptr] = nullptr;

        while(cur) {
            auto tmp = new Node(cur->val, nullptr, nullptr);
            cur2->next = tmp;
            node_map[cur] = tmp;
            cur = cur->next;
            cur2 = cur2->next;
        }

        cur = head;
        cur2 = res;
        // hash_map 如果存储了多个nullptr
        while (cur) {
            cur2->random = node_map[cur->random];
            cur = cur->next;
            cur2 = cur2->next;
        }
        return res;
    }
};

// https://www.cnblogs.com/grandyang/p/4261431.html
// 这种方法非常巧妙 解释参考
class Solution2 {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        auto cur = head;
        // 1(2) -> 2(3) -> 3(1)
        while(cur) {
            auto tmp = new Node(cur->val, nullptr, nullptr);
            tmp->next = cur->next;
            cur->next = tmp;
            cur = tmp->next;
        }
        // 1(2) -> 1(null) -> 2(3) -> 2(null) -> 3(1) -> 3(null)

        // 2. 深拷贝
        cur = head;
        while (cur) {
            // cur->random表示随机指针指向的节点 但是深拷贝要指向新的节点 所以next
            // cur->random->next 就是之前新加的随机点
            if (cur->random) cur->next->random = cur->random->next;
            cur = cur->next->next;
        }

        cur = head;
        auto res = head->next;
        while (cur) {
            auto t = cur->next;
            cur->next = t->next; // 从链表删除节点的正常步骤
            if (t->next) t->next = t->next->next;
            cur = cur->next;
        }
        return res;
    }
};