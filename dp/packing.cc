#include <iostream>
#include <vector>
#include <cstring> // memset()
#include <string> // memset()
using namespace std;

// http://imwyy.xyz/2018/01/24/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E4%B9%8B%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E5%8F%8Aleetcode%E5%AE%9E%E4%BE%8B/
// https://www.liwei.party/2018/09/21/leetcode-solution/dynamic-programming-7/#toc-heading-2
// https://zhuanlan.zhihu.com/p/93857890
// 背包问题 最优的定义 : 1. 只要收益最大  2. 背包完全装满

// @TODO
// 动态规划问题 往往把函数需要的参数  用一个数字表示范围
//  比如[a, b]  ==>  b
//  因为 最小边界a是默认的 , b则可以当作滑动窗口
#define MAX(a, b) ((a) > (b) ? (a) : (b))

template<class T>
void printVector(vector<vector<T>> const &mat) {
	for (vector<T> row: mat) {
		for (T val: row) {
			cout << val << "\t";
		}
		cout << '\n';
	}
}

namespace pack1 {
int n = 6;
int volume[10] = {4, 2, 6, 4, 2, 10};
int need[10] = {7, 10, 6, 7, 5, 4};
string name[10] = {"laptop", "camera", "xbox", "grinder", "dumbell", "encyclopedia"};
vector<vector<int>> cache(20, vector<int>(10, -1));
vector<vector<int>> p(20, vector<int>(10, 0));

// capacity, item各自的取值范围 [0,w] 和 [0,n]  子问题个数是 O(nw), 可以在常数时间内解决 O(nw)
// item:表示物品的序号 实际上是一个物品序号范围 [item...]   item 只有0/1两种选择
// pack01(capacity, item) = 容积剩余capacity时, 放入(item以后的物品)能够获得的最大收益
int pack01(int capacity, int item) {
    // @NOTE item+1 == n 可能最后一件item就没有参与计算 不符合逻辑
	if(item == n) return 0;   // 无可放的物品

	int& ret = cache[capacity][item];
	if(ret != -1) return ret;

    // 不带走当前item
	ret = pack01(capacity, item + 1);
    cout << item << "|";
	if(capacity >= volume[item]) {
        // 带走当前的item
        cout << endl;
        auto cand = pack01(capacity-volume[item], item+1) + need[item];
        if(cand > ret) {
            ret = cand;
        }
    }
    if ( pack01(capacity, item+1) != pack01(capacity, item) ) {
        p[capacity][item] = 1;
    }

    return ret;
}

// 无法逆序追踪出来
// 把 pack(capacity, item)选择出的物品保存到 picked
// 有点像二叉树
void reconstruct(int capacity, int item, vector<string>& picked) {
	if(item == n) return;
	if(pack01(capacity, item) == pack01(capacity, item+1))
	    reconstruct(capacity, item+1, picked);
	else {
		picked.push_back(name[item]);
		reconstruct(capacity-volume[item], item+1, picked);
	}
}

// 复现路径 必须按照递归的思路 但是暂时没有想明白 @TODO
// void re(vector<string>& picked) {
//     for (int i=0; i<p.size(); i++) {
//         if(p[i] != 0)
//             picked.push_back(name[i]);
//     }
// }
}

namespace pack2 {

int n = 4; // vo = 5
int volume[10] = {1, 2, 3, 4};
int need[10] = {2, 4, 4, 5};
int cache[1001][100];

int packInf(int capacity, int item) {
    // @NOTE item+1 == n 可能最后一件item就没有参与计算 不符合逻辑
	if(item == n) return 0;   // 一定会从0号物品 遍历到 n-1号物品

	int& ret = cache[capacity][item];
	if(ret != -1) return ret;

    // 不带走当前item
	ret = packInf(capacity, item + 1);
    for(int k=1; capacity >= (k*volume[item]); k++) {
        auto benefit = k * need[item];
        auto room = k * volume[item];
        auto cand = packInf(capacity-room, item+1) + benefit;

        // 带走当前的k件item
        if(cand > ret) {
            ret = cand;
        }
    }
    return ret;
}

void reconstruct(int capacity, int item, vector<int>& picked) {
	if(item == n) return;
	if(packInf(capacity, item) == packInf(capacity, item+1))
	    reconstruct(capacity, item+1, picked);
	else {
        for(int k=1; capacity >= (k*volume[item]); k++) {
            ++picked[item];
            auto room = k * volume[item];
            reconstruct(capacity-room, item+1, picked);
        }
	}
}



}

namespace pack3 {
// 多重背包问题 与 完全背包的区别 : 判断物件数量不超过 限制

int n = 4; // vo = 5
int volume[10] = {1, 2, 3, 4};
int need[10] = {2, 4, 4, 5};
int cache[1001][100];

int packInf(int capacity, int item) {
    // @NOTE item+1 == n 可能最后一件item就没有参与计算 不符合逻辑
	if(item == n) return 0;   // 一定会从0号物品 遍历到 n-1号物品

	int& ret = cache[capacity][item];
	if(ret != -1) return ret;

    // 不带走当前item
	ret = packInf(capacity, item + 1);
    for(int k=1; /* k<= nums[item] && */capacity >= (k*volume[item]); k++) {
        auto benefit = k * need[item];
        auto room = k * volume[item];
        auto cand = packInf(capacity-room, item+1) + benefit;

        // 带走当前的k件item
        ret = MAX(ret, cand);
    }
    return ret;
}
}

int main() {
    // {
    //     using namespace pack1;
    //     // memset(cache, -1, sizeof(cache));
    //     int capacity = 10;
    //     cout << "res: " << pack01(capacity, 0) << endl;

    //     // for(auto i : p) cout << i << " ";
    //     cout << endl;
    //     // printVector(p);
    // }
    {
        using namespace pack2;
        int capacity = 5;
        int cnt = packInf(capacity, 0);
        cout << "res=" << cnt << endl;

        // for(auto i : p) cout << i << " ";
        vector<int> tmp;
        reconstruct(capacity, 0, tmp);
        for(auto i : tmp) cout << i << " ";
        cout << endl;
        // cout << endl;
    }
    /*
    vector<string> tmp;
    re(tmp);
    // reconstruct(capacity, 0, tmp);
    for(auto i : tmp) cout << i << " ";
    cout << endl;
*/
    return 0;
}