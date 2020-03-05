#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

// 原地反转 @SEE string/151
// https://leetcode.com/problems/rotate-array/solution/
// 解法3的思路非常直接
//  Input: [1,2,3,4,5,6,7] and k = 3
// Output: [5,6,7,1,2,3,4]
void rotate3(vector<int>& nums, int k) {
    const int n = nums.size(); k %= n;
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin()+k);
    std::reverse(nums.begin()+k, nums.end());
}

// https://www.cnblogs.com/grandyang/p/4298711.html
void rotate(vector<int>& nums, int k) {
    const int n = nums.size();
    vector<int> t = nums;
    for (int i = 0; i < n; ++i) {
        nums[(i + k) % n] = t[i];
    }
}

// 所有的位置都是正确的 只要记录k
// 因为count记录了循环的次数 时间 O(n)
void rotate2(vector<int>& nums, int k) {
    const int n = nums.size(); k %= n;
    int count = 0;
    for (int start = 0; count < n; start++) {
        int current = start;
        int prev = nums[start];
        do {
            int next = (current + k) % n;
            std::swap(nums[next], prev);
            // int temp = nums[next]; nums[next] = prev; prev = temp;
            current = next;
            count++;
        } while (start != current);
    }
}

// https://blog.csdn.net/Hackbuteer1/article/details/6699837
// http://blog.thpiano.com/?p=251
// 循环右移数组
// (XTYT)T=(YT)T(XT)T=YX
// 循环右移相当于一个旋转罗盘  记住取模
int main() {
    std::vector<int> v{1,2,3,4,5,6};
    int k = 2;

    rotate3(v, k);
    for(auto e : v) std::cout << e;
    std::cout << '\n';
    const int n = v.size(); k= n-k;
    rotate3(v, k);k= n-k;

    std::reverse(v.begin(), v.end()-k);
    for(auto e : v) std::cout << e;
    std::cout << '\n';

    std::reverse(v.rbegin(), v.rbegin()+k);
    for(auto e : v) std::cout << e;
    std::cout << '\n';

    std::reverse(v.begin(), v.end());
    for(auto e : v) std::cout << e;
    std::cout << '\n';

    return 0;
}