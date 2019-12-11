#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

// 简单无向图
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors = {}) {
        val = _val;
        neighbors = _neighbors;
    }
};

// https://www.cnblogs.com/grandyang/p/4267628.html
// BFS 更好理解  图的遍历只有两种方式DFS/BFS
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        //      src_graph  -->  dest_neighbors
        unordered_map<Node*, Node*> node_map;
        queue<Node*> Q;
        Q.push(node);
        auto clone = new Node(node->val, {});
        node_map[node] = clone;

        while (!Q.empty()) {
            auto tmp = Q.front();
            Q.pop();
            for (auto neighbor : tmp->neighbors) {
                if (!node_map.count(neighbor)) {  // 如果neighbor是第一次记录, 队列要保存
                    node_map[neighbor] = new Node(neighbor->val);
                    Q.push(neighbor);
                }
                // 原节点 到 新节点的映射
                node_map[tmp]->neighbors.push_back(node_map[neighbor]);
            }
        }
        return clone;
    }
};