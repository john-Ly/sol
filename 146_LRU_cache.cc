#include <list>
#include <utility>
#include <iterator>
#include <unordered_map>
using namespace std;


// https://songlee24.github.io/2015/05/10/design-LRU-Cache/

// https://leetcode.com/problems/lru-cache/discuss/45976/C++11-code-74ms-Hash-table-+-List/225468
// 应该是LRU <-- MRU  (作为基础软件 更应该注意性能 其他高效的实现方法 注意下)
//
// 关键是 get/put 均为 O(1)复杂度
// https://www.cnblogs.com/grandyang/p/4587511.html
// https://zhuanlan.zhihu.com/p/40399701
class LRUCache{
public:
    LRUCache(int capacity) : cap(capacity) { }

    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) return -1;
        l.splice(l.begin(), l, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = m.find(key);
        if (it != m.end()) l.erase(it->second);
        l.push_front(make_pair(key, value));
        m[key] = l.begin();
        if (m.size() > cap) {
            int k = l.rbegin()->first;
            l.pop_back();
            m.erase(k);
        }
    }

private:
    int cap;
    //        key  value
    list<pair<int, int>> l;  // 访问容器 需要保证LRU的顺序

    // 保证O(1)
    // hash存储 key --> iterator 的映射(不会因为链表元素的位置变化而失效)
    unordered_map<int, decltype(l.begin())> m;
    // unordered_map<int, list<pair<int, int>>::iterator> m;
};