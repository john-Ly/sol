#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// 1. https://www.techiedelight.com/use-std-pair-key-std-unordered_map-cpp/
// 为什么unorderd_map 不能针对pair进行hash + 普遍推荐boost::hash_combine
// str化pair 里面的数据

// 2. https://leetcode.com/problems/max-points-on-a-line/discuss/47124/C%2B%2B-slope-counter
// 详细的解释

// 3. 表示斜率 dy/dx 但是两个double类型的数据进行除法 可能会导致无限循环小数+ 分母为0+ 精度丢失
// 总之 double 的除法应该尽可能避免
// 利用模运算更高效的算法
int gcd(int p, int q) {
	if(q == 0) return p;
	return gcd(q, p%q);
}

int maxPoints(vector<vector<int>>& points) {
    int n = points.size(), ans = 0;
    // 计算所有可能的线段组合情况
    for (int i = 0; i < n; i++) {
        unordered_map<string, int> counter;
        int dup = 1;
        for (int j = i + 1; j < n; j++) {
            // 两个点重合
            if (points[j][0] == points[i][0] && points[j][1] == points[i][1]) {
                dup++;
            } else {
                // https://www.cnblogs.com/grandyang/p/4579693.html
                // 因为使用了str 故不用考虑斜率不存在的情况
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                int g = gcd(dx, dy);
                counter[to_string(dx / g) + '_' + to_string(dy / g)]++;
            }
        }
        ans = max(ans, dup);
        for (auto p : counter) {
            ans = max(ans, p.second + dup);
        }
    }
    return ans;
}