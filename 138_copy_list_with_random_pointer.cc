#include <iostream>
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

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        auto cur = head;
        auto res = new Node(cur->val, nullptr, nullptr);
        unordered_map<Node*, Node*> node_map;
        node_map[cur] = cur->random;

        while(cur->next) {
            auto tmp = new Node(cur->next->val, nullptr, nullptr);
            res->next = tmp;
            node_map[cur->next] = cur->next->random;
            cur = cur->next;
        }

    }
};