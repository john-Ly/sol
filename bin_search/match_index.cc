#include <vector>
#include <iostream>
using namespace std;

// 无重递增
int findMatchIndex(vector<int>& v) {
    if (v[0] > ((int)v.size()-1)) return -1;
    if (v.back() < 0) return -1;

    int le = 0, ri = v.size();
    while (le < ri) {
        int mid = (le + ri) / 2;
        if (v[mid] < mid) le = mid+1;
        else ri = mid;
    }
    // cout << le << '-' << ri << v[ri] << endl;
    return (v[ri] == ri) ? ri : -1;
}

int main(int argc, char *argv[])
{
    vector<int> v = {-1, 1, 4, 5};
    cout << findMatchIndex(v) << endl;
    return 0;
}
