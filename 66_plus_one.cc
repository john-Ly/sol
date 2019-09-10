#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4079357.html

vector<int> plusOne(vector<int> &digits) {
    int n = digits.size();
    for (int i = n - 1; i >= 0; --i) {
        if (digits[i] == 9) digits[i] = 0;
        else {
            digits[i] += 1;
            return digits;
        }
    }

    // 遍历了所有位, 即9...9
    if (digits.front() == 0) digits.insert(digits.begin(), 1);
    return digits;
}


vector<int> plusOne1(vector<int>& digits) {
    if (digits.empty()) return digits;
    // 加1 == 虚拟进位为1
    int carry = 1, n = digits.size();
    for (int i = n - 1; i >= 0; --i) {
        if (carry == 0) return digits;

        int sum = digits[i] + carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }

    // 遍历了所有位, 即9...9
    if (carry == 1) digits.insert(digits.begin(), 1);
    return digits;
}

int main() {
    vector<int> a = {4, 3, 9, 9};
    auto tmp = plusOne1(a);
    for (auto i : tmp)
        cout << i << ' ';
    cout << endl;
    return 0;
}