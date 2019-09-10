#include <iostream>
#include <stack>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4091064.html
namespace so1 {
class MinStack {
public:
    MinStack() {}

    void push(int x) {
        s1.push(x);
        // s2实际上维护了一个单调栈
        if (s2.empty() || x <= s2.top()) s2.push(x);
    }

    void pop() {
        // 如果s1.pop删除的就是最小元素, s2也要更新 维护一致性
        if (s1.top() == s2.top()) s2.pop();
        s1.pop();
    }

    int top() {
        return s1.top();
    }

    int getMin() {
        return s2.top();
    }

private:
    // s1存放原始数据, s2存放目前数据的最小值
    stack<int> s1, s2;
};
}

namespace so2 {
class MinStack {
public:
    MinStack() : min_val(INT_MAX){ }

    // min实际上会有历史版本存放在stack中
    // 如果x 是最小的, 那么先把min压栈, x再压栈
    //     | x |  -> new_min
    //     |min|  -> last_min
    void push(int x) {
        if (x <= min_val) {
            st.push(min_val);
            min_val = x;
        }
        st.push(x);
    }

    void pop() {
    //     | x |  -> new_min
    //     |min|  -> last_min
        int t = st.top(); st.pop();
        if (t == min_val) {  // 如果pop的数字就是new_min, 保持一致性
            min_val = st.top(); st.pop();
        }
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return min_val;
    }

private:
    int min_val;
    stack<int> st;
};
}