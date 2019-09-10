#include <vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4059650.html

// m, n : 两个数组初始化时元素的个数
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    // 可能i也有剩余 不过是放在nums1数组中 所以可以不考虑
    while (j >= 0) nums1[k--] = nums2[j--];
}

int main() {
    vector<int> v1 {1,2,3,0,0,0};
    vector<int> v2 {2,5,6};
    merge(v1, 3, v2, 3);

    for(const auto& i : v1)
    cout << i << " ";
    cout << endl;

    return 0;
}