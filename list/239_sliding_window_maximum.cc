#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>   // priority_queue
#include <utility> // pair
#include <set>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4656517.html
namespace so1 {
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    // multiset使用红黑树保证排序(升序)
    multiset<int> st;

    // i: [0- nums.size()-k]
    // 如8个数, k=3, i的取值范围[0, 5]
    for (int i = 0; i < nums.size(); ++i) {
        // k=3, i=3, 说明0是不再窗口内 删除左边界  nums[i-k]
        // multiset erase(key) 会删除所有的key, 所以使用iterator 只删除特定位置
        if (i >= k) st.erase(st.find(nums[i - k]));
        st.insert(nums[i]);
        // 目前窗口已经维护好
        // @TODO 此处可以做流水线 窗口值可以在循环前初始优化 循环就不会有if判断
        if (i >= k - 1) res.push_back(*st.rbegin());
    }
    return res;
}
}

namespace so2 {
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    // 最大堆 first: 数字, second: 位置(下标)
    priority_queue<pair<int, int> > q;

    for (int i = 0; i < nums.size(); ++i) {
        // 窗口pre, 窗口cur
        // cur窗口新增的元素只要和pre窗口里的最大值比较 也就判断出cur窗口的最大值
        // pq.top默认是pre窗口的最大 这个座标在窗口内部, 保留; 否则删除
        // 用循环是因为pq只是保留top, multiset则是全部排序
        while (!q.empty() && q.top().second <= i - k) q.pop();
        // if(!q.empty())
        //     cout << q.size() << endl;
        q.push({nums[i], i});
        if (i >= k - 1) res.push_back(q.top().first);
    }

    return res;
}
}

// 维护一个单调队列(deque双向队列)
namespace so3 {
// 滑动窗口 [i-(k-1), i]  when: i>=(k-1)
// k=3, i=3, 说明0是不再窗口内 [1, 3]

//https://leetcode.com/problems/sliding-window-maximum/discuss/65884/Java-O(n)-solution-using-deque-with-explanation
// https://leetcode.com/problems/sliding-window-maximum/discuss/65898/Clean-C%2B%2B-O(n)-solution-using-a-deque

// 维护一个单调队列 a[x] <a[i] and x<i  (集合里面的任意一个元素)
// Time: O(n)
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    deque<int> q; // 存储下标

    // 进入循环前: q保存针对老窗口维护的单调队列, i则是要新窗口要加入的元素
    for (int i = 0; i < nums.size(); ++i) {
        // 1. 队头要存储还在窗口内的最大值, 过期了( <= i-k) 所以就从窗口移除)
        if (!q.empty() && q.front() <= i - k) q.pop_front();
        // 2. 如果要入队的数 比集合中最后一个大 那么队列要删除没用的元素  保证单调性
        while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
        // 3. 队尾加入
        q.push_back(i);
        if (i >= k - 1) res.push_back(nums[q.front()]);
    }
    return res;
}
}

int main () {
    vector<int> v {1,3,-1,-3,5,3,6,7};
    int k = 3;
    // for (auto i: so1::maxSlidingWindow(v, k))
    //     cout << i << " ";
    // cout << endl;

    // for (auto i: so2::maxSlidingWindow(v, k))
    //     cout << i << " ";
    // cout << endl;

    for (auto i: so3::maxSlidingWindow(v, k))
        cout << i << " ";
    cout << endl;

    return 0;
}