#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// a mapping from each element to its number of appearances
int majorityElement(vector<int>& nums) {
    // @TODO count initialization is 0
    unordered_map<int, int> counts; 
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        if (++counts[nums[i]] > n / 2)
            return nums[i];
    }
}

int main () {
    vector<int> v {2,2,1,1,1,2,2};
    int tmp = majorityElement(v);

    std::cout << tmp << std::endl;
    return 0;
}
