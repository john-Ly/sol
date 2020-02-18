#include <climits>
#include <vector>
#include <iostream>
using namespace std;

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
    return (third == LONG_MIN || third == second) ? first : third;
    // 选取的数字是严格小于; third 不会和second相等
    // (如果只有一个数, third==second; 但是第一个判断条件足够)
}

int main( )
{
    vector<int> v = {3, 2, 2, 1};
    cout << thirdMax(v) << endl;
    return 0;
}
