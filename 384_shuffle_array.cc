#include <vector>
#include <iostream>
using namespace std;

// 当内存无法加载全部数据时，如何从包含未知大小的数据流中随机选取k个数据，并且要保证每个数据被抽取到的概率相等。
// topic: 蓄水池算法(采样)
// 概率抽样
// 10TB的日志, 等概率随机抽取k条日志 采样
// https://zhuanlan.zhihu.com/p/29178293  详细的公式证明
// https://leetcode.com/problems/linked-list-random-node/discuss/85659/Brief-explanation-for-Reservoir-Sampling
// https://github.com/linghuazaii/blog/wiki/%5BAlgorithm%5D%E7%99%BE%E5%BA%A6%EF%BC%9A%E8%93%84%E6%B0%B4%E6%B1%A0%E6%8A%BD%E6%A0%B7

namespace {
vector<int> ReservoirSampling(vector<int>& results, vector<int>& nums, int k) {
    // results.size(): k
    // nums.size(): N
    // N >> k
    int N = nums.size();
    // 前k个数，我们全部保留
    // 第i（i>k）个数，以 (k/i) 的概率保留第i个数，并以 [公式] 的概率与前面已选择的k个数中的任意一个替换。

    for (int i=0; i<k; ++i) {
        results[i] = nums[i];
    }

    for (int i=k; i<N; ++i) {
        int random = rand()%i; // [0, i-1]
        // random 落在[0, k-1]  ==>  说明第i个数进入池子
        //            [k, i-1]  ==>  第i个数丢弃
        if (random<k) {
            results[random] = nums[i];
        }
    }

    return results;
}
}

namespace sol_382 {
// 返回链表中的一个结点, 每个点都等概率
// N个数  k==1
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class list_random_node {
    ListNode *head;
public:
    explicit list_random_node(ListNode* _head) : head(_head) {}

    int getRandom() {
        int res = head->val, i = 2; // i记录当前遍历的数目
        ListNode *cur = head->next;
        while (cur) {
            int j = rand() % i;
            if (j == 0) res = cur->val;  // 保留cur的数据
            ++i;
            cur = cur->next;
        }
        return res;
    }
};

}

// https://yjk94.wordpress.com/2017/03/17/%E6%B4%97%E7%89%8C%E7%9A%84%E6%AD%A3%E7%A1%AE%E5%A7%BF%E5%8A%BF-knuth-shuffle%E7%AE%97%E6%B3%95/
// https://www.cnblogs.com/grandyang/p/5783392.html
// 介绍kunth_洗牌算法
// 排列问题 N! 保证出现的结果始终是 等概率的
namespace sol_384 {

vector<int> shuffle(const vector<int>& origin) {
    vector<int> res = origin;
    // 在拿起第i张牌时，只从它前面的牌随机选出j，而不是从整副牌里面随机选取
    // 在 i-n之前随机选取一个座标 跟blog里面介绍的不相同 @TODO
    for (int i = 1; i < res.size(); ++i) {
        int t = i + rand() % (res.size() - i);
        swap(res[i], res[t]);
    }
    return res;
}

}

namespace randomPrint {
// 无重数组等概率 打印M个数
void PrintMRandom (const vector<int>& v, int m) {
    int n = v.size();
    for (int i=0; i<m; ++i) {
        int random = rand()%(n-i);
        cout << v[random] << '-';
        swap(v[random], v[n-i-1]);
    }
}

    // @TODO 不太理解 等概率输出M个数M

}