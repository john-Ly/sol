#include <unordered_set>

// e.g.

// 19 -> 82 -> 68 -> 100 -> 1(最终会循环)
//
bool isHappy(int n) {
    unordered_set<int> st;

    while (n != 1) {
        int sum = 0;
        // 对每一位进行 平方相加
        while (n) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        n = sum;
        if (st.count(n)) break;
        st.insert(n);
    }
    return n == 1;
}

namespace sol2 {
// https://www.cnblogs.com/grandyang/p/4447233.html
// 非常巧妙 利用了快慢指针(因为最终结果会停留在1)
bool isHappy(int n) {
    int slow = n, fast = n;
    while (true) {
        slow = findNext(slow);
        fast = findNext(fast);
        fast = findNext(fast);
        if (slow == fast) break;
    }
    return slow == 1;
}

// 计算各位数字平方和
int findNext(int n) {
    int res = 0;
    while (n > 0) {
        res += (n % 10) * (n % 10);
        n /= 10;
    }
    return res;
}
}


// https://www.cnblogs.com/grandyang/p/4741028.html
// 258_add_digits  求数根(把每个digit相加 知道结果小于10)
int addDigits(int num) {
    while (num / 10 > 0) {

        // 可以抽象出一个函数
        ///////////////
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        ///////////////

        num = sum;
    }
    return num;
}

// 每9个一循环
// >9 的数的树根都是对9取余，那么对于等于9的数对9取余就是0了
// corner-case: 0
int addDigits(int num) {
    return (num == 0) ? 0 : (num - 1) % 9 + 1;
}