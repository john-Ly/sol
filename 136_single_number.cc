#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4130577.html

int singleNumber(vector<int>& nums) {
    unordered_set<int> set;
    int n = nums.size();
    for(int num : nums) {
        if(set.count(num)) set.erase(num);
        else set.insert(num);
    }

    return *set.begin();
}

// 位运算 异或具有交换律
int singleNumber_bit(vector<int>& nums) {
    int res = 0;
    for (auto num : nums) res ^= num;
    return res;
}

int main () {
    vector<int> v {2,1,2};
    int tmp = singleNumber(v);

    std::cout << tmp << std::endl;
    return 0;
}
