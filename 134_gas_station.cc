#include <iostream>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4266812.html
// 环形加油站 (能否从一个站灌满油 出发到下一站 环一周)
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    // total: 总的加油站油量 >= 路程
    int total = 0
    int sum = 0, start = 0;
    for (int i = 0; i < gas.size(); ++i) {
        total += gas[i] - cost[i];

        sum += gas[i] - cost[i];
        // 从起点到这个点中间的任何一个点都不能作为起点，则把起点设为下一个点，继续遍历。
        if (sum < 0) {
            start = i + 1;
            sum = 0;
        }
    }
    return (total < 0) ? -1 : start;
}