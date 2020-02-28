#include <iostream>
#include <vector>
using namespace std;

// topological: BFS 利用入度信息
// https://www.cnblogs.com/grandyang/p/4484571.html
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 构造graph和每个结点入度信息
        vector<vector<int>> graph(numCourses, vector<int>());
        vector<int> in(numCourses, 0);
        for (auto a : prerequisites) {
            graph[a[1]].push_back(a[0]);
            ++in[a[0]];
        }

        queue<int> q;
        // 2. 所有入度为0的点放进队列, 如果没有说明一定有环存在 [1,2] [2,1]
        for (int i = 0; i < numCourses; ++i) {
            if (in[i] == 0) q.push(i);
        }
        // 3. 每次都把入度为0的点 删除 并且更新其相关结点
        while (!q.empty()) {
            int t = q.front(); q.pop();
            numCourses--;
            for (auto a : graph[t]) {
                --in[a];
                if (in[a] == 0) q.push(a);
            }
        }
        // https://leetcode.com/problems/course-schedule/discuss/58509/C++-BFSDFS/195152
        return numCourses == 0;
        // 所有结点的入度都为0 否则有环
        // for (int i = 0; i < numCourses; ++i) {
        //     if (in[i] != 0) return false;
        // }
        // return true;
    }
};

namespace topo {
// https://www.cnblogs.com/grandyang/p/4504793.html
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> res;
        vector<vector<int>> graph(numCourses, vector<int>());
        vector<int> in(numCourses, 0);
        for (auto a : prerequisites) {
            graph[a[1]].push_back(a[0]);
            ++in[a[0]];
        }

        queue<int> q;
        // 2. 所有入度为0的点放进队列, 如果没有说明一定有环存在 [1,2] [2,1]
        for (int i = 0; i < numCourses; ++i) {
            if (in[i] == 0) q.push(i);
        }
        // 3. 每次都把入度为0的点 删除 并且更新其相关结点
        while (!q.empty()) {
            int t = q.front(); q.pop();
            res.push_back(t);
            for (auto a : graph[t]) {
                --in[a];
                if (in[a] == 0) q.push(a);
            }
        }
        if (res.size() != numCourses) return vector<int>();
        return res;
    }
};
}