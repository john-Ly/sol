#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

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
