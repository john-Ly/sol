#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

// topic: hash表 排序

// leetcode 387
// 返回字符串只出现一次的字符(建立hash表)
// string += ch
int firstUniqChar(string s) {
    // unordered_map<char, int> m;
    int m[128] = {0};
    for (char c : s) ++m[c];
    for (int i = 0; i < s.size(); ++i) {
        if (m[s[i]] == 1) return i;
    }
    return -1;
}

// leetcode 451
// https://www.cnblogs.com/grandyang/p/6231504.html
namespace string_freq {
    // 1. string中统计字符出现次数 并且降序输出
    //   a. hash map统计
    //   b. 排序(按照特定规则 桶排序或者堆排序)
    string frequencySort(string s) {
        string res = "";
        priority_queue<pair<int, char>> q;
        unordered_map<char, int> m;
        for (char c : s) ++m[c];
        for (auto a : m) q.push({a.second, a.first});
        while (!q.empty()) {
            auto t = q.top(); q.pop();
            res.append(t.first, t.second);
        }
        return res;
    }

    string frequencySort1(string s) {
        string res = s;
        unordered_map<char, int> m;
        for (char c : res) ++m[c];
        // order(freq, alphabet)
        std::sort(s.begin(), s.end(), [&](char& a, char& b){
            return m[a] > m[b] || (m[a] == m[b] && a < b);
        });
        return s;
    }

    // 计数排序
    string frequencySort2(string s) {
        string res;
        vector<string> v(s.size() + 1);

        // 每个字符出现的次数 最少1次 最多size()次
        unordered_map<char, int> m;
        for (char c : s) ++m[c];

        // 每个桶是 次数
        for (auto &a : m) {
            v[a.second].append(a.second, a.first);
        }
        // 从最后一个开始: 次数为s的长度的桶
        for (int i = s.size(); i > 0; --i) {
            if (!v[i].empty()) res.append(v[i]);
        }
        return res;
    }

// map_reduce的思想
// https://www.cnblogs.com/grandyang/p/5386475.html
// grep -oE '[a-z]+' words.txt | sort | uniq -c | sort -nr | awk '{print $2" "$1}'
// grep -E 采用扩展的BRE
// uniq -c 采用计数器模式
// sort r: reverse降序 按照n数字
}

// https://www.cnblogs.com/grandyang/p/5454125.html
// https://www.cnblogs.com/grandyang/p/7689927.html
namespace big_data {

// 统计出现次数最多的 entry, 输出前k个
vector<int> topKFrequent_1(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    priority_queue<pair<int, int>> q;
    vector<int> res;
    for (auto a : nums) ++m[a];  // 记录出现的次数
    for (auto it : m) q.push({it.second, it.first});  // 建立大根堆

    for (int i = 0; i < k; ++i) {
        res.push_back(q.top().second); q.pop();
    }

    return res;
}

// 最小堆 @NOTE
// priority_queue<int, vector<int>, greater<int> > pq;
// vector<string> topKFrequent(vector<string>& words, int k) {
//     vector<string> res(k);
//     unordered_map<string, int> freq;
//     auto cmp = [](pair<string, int>& a, pair<string, int>& b) {
//         return a.second > b.second || (a.second == b.second && a.first < b.first);
//     };
//     // 最小堆的排序规则 是greater  最大堆是less<>
//     priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp) > q(cmp);
//     for (auto word : words) ++freq[word];
//     // 遍历 每次容量超出删除当前最小的; 结束后只剩下前k个
//     for (auto f : freq) {
//         q.push(f);
//         if (q.size() > k) q.pop();
//     }
//     for (int i = res.size() - 1; i >= 0; --i) {
//         res[i] = q.top().first; q.pop();
//     }
//     return res;
// }

// 使用计数排序的变形 (二维矩阵)
vector<int> topKFrequent_2(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    // 桶的个数 (最差情况 nums只有一个数 出现了size次)
    vector<vector<int>> bucket(nums.size() + 1);
    vector<int> res;
    for (auto a : nums) ++m[a];

    for (auto it : m) {
        bucket[it.second].push_back(it.first);
    }

    // 逆序输出即可
    for (int i = nums.size(); i > 0; --i) {
        // @TODO 先估算当前桶全部+res.size <= k ==> 直接insert
        // >k 则要一个一个的添加 或者iterator
        for (int j = 0; j < bucket[i].size(); ++j) {
            res.push_back(bucket[i][j]);
            if (res.size() == k) return res;
        }
    }
    return res;
}
}

namespace kth_element {

// leetcode 414
// O(n) 算法 因为求得个数较小
// 否则利用堆排序 需要O(n lg n)

#include <climits>
class thirdMax_sol {
// 如果不存在第三大unique, 返回第一大 (重复数字不算)
// { 2, 2, 3, 1} ==> 1
int thirdMax(vector<int>& nums) {
    long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
    for (int num : nums) {
        if (num > first) {
            third = second;
            second = first;
            first = num;
        } else if (num > second && num < first) {
            third = second;
            second = num;
        } else if (num > third && num < second) {
            third = num;
        }
        cout << first << second << third << endl;
    }
    return (third == LONG_MIN) ? first : third;
    // return (third == LONG_MIN || third == second) ? first : third;
    // 选取的数字是严格小于; third 不会和second相等
    // (如果只有一个数, third==second; 但是第一个判断条件足够)
}

};

// leetcode 703
// 使用最小堆, 处理无限流量的数据
// 维护大小k个的窗口
// https://www.cnblogs.com/grandyang/p/9941357.html
class KthLargest {
// 降序排列 取出第k个数
public:
    // 构造函数先对初始的部分求出kth_element(如果排序)
    KthLargest(int k, vector<int> nums) : k_(k) {
        for (int num : nums) {
            q.push(num);
            if (q.size() > k_) q.pop();
        }
    }

    int add(int val) {
        q.push(val);
        if (q.size() > k_) q.pop();
        return q.top();
    }

private:
    // 最小堆
    priority_queue<int, vector<int>, greater<int>> q;
    int k_;
};

// 快排如何划分(三路归并)
// quick_select
int partition(vector<int>& nums, int left, int right) {
    // 1. 第一个元素作为pivot
    int pivot = nums[left], l = left + 1, r = right;
    // 2. 循环退出时, r指向左边的区域的最后一个
    while (l <= r) {
        if (nums[l] < pivot && nums[r] > pivot) {
            swap(nums[l++], nums[r--]);
        }
        if (nums[l] >= pivot) ++l;
        if (nums[r] <= pivot) --r;
    }
    swap(nums[left], nums[r]);
    return r;
}

// leetcode 215
// https://www.cnblogs.com/grandyang/p/4539757.html
int findKthLargest(vector<int>& nums, int k) {
    int left = 0, right = nums.size() - 1;
    while (true) {
        int pos = partition(nums, left, right);
        if (pos == k-1) return nums[pos];
        if (pos > k-1) right = pos-1;
        else left = pos+1;
    }
}
}

namespace quick_sort_sedgewich {
void quick_sort(vector<int>& nums, int left, int right) {
    if (left == right) return;

    // 1. 第一个元素作为pivot
    int pivot = nums[left], l = left + 1, r = right;

    // 2. 循环退出时, r指向左边的区域,
    while (l <= r) {
        if (nums[l] < pivot && nums[r] > pivot) {
            swap(nums[l++], nums[r--]);
        }

        if (nums[l] >= pivot) ++l;
        if (nums[r] <= pivot) --r;
    }
    swap(nums[left], nums[r]);

    quick_sort(nums, left, r);
    quick_sort(nums, l, right);
}

void driver() {
    std::vector<int> v = {32,71,12,45,26,80,53,33,36,45};
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));

    // for(int elem : v) std::cout << elem << ' ';
    std::cout << "\n";
    quick_sort(v, 0, v.size()-1);

    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

}

int main()
{
    quick_sort_sedgewich::driver();
    return 0;
}
