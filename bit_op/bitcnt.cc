#include <iostream>
using namespace std;

int numberOf1(int n) {
    assert(n>=0);
    int cnt = 0;
    while (n) {
        if (n & 1u) ++cnt;
        n >>= 1;
    }
    return cnt;
}

int main(int argc, char *argv[])
{
    cout << numberOf1(0) << endl;
    cout << numberOf1(1) << endl;
    cout << numberOf1(2) << endl;
    cout << numberOf1(7) << endl;
    return 0;
}
