#include <iostream>
#include <stack>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4091064.html
// push pop getMin 的时间复杂度 O(1)
namespace so1 {
class MinStack {
public:
    MinStack() {}

    void push(int x) {
        s1.push(x);
        // s2实际上维护了一个单调栈 (等于的情况: 因为两个栈同步操作)
        if (s2.empty() || x <= s2.top()) s2.push(x);
    }

    void pop() {
        // 如果s1.pop删除的就是最小元素, s2也要更新 维护一致性
        if (s1.top() == s2.top()) s2.pop();
        s1.pop();
    }

    int top() { return s1.top(); }
    int getMin() { return s2.top(); }

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

// 题1. 利用两个栈结构实现队列
// stack_enqueue + stack_dequeue
// 每次要pop的时候 先把push栈全部装入pop栈(1.要全部装入 2.pop栈必须为空)
class stack_queu {
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()){
            while(stack1.size() > 0){
                int data = stack1.top();
                stack1.pop();
                stack2.push(data);
            }
        }
        int pop_element = stack2.top();
        stack2.pop();
        return pop_element;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

// 题2. 一个栈 排序(使用一个辅助栈)
// 辅助栈先尽量保持排序 再申请一个变量暂存 类似汉诺塔

// 题3: 给顶一个入栈顺序, 判断一个出栈顺序是否可能发生
class sol3 {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(pushV.size() == 0) { return false; }

        // pushV: 1 2 3 4 5
        //  popV: 4 5 3 2 1  可能 按顺序压入1 2 3 4 -> 出栈4 -> 压入5 -> 顺序出栈
        for(int i = 0, j = 0; i < pushV.size();i++){
            stackData.push(pushV[i]);
            while(j < popV.size() && stackData.top() == popV[j]){
                stackData.pop();
                j++;
            }
        }
        return stackData.empty();
    }

private:
    stack<int> stackData;
};