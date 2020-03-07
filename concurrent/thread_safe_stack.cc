#include <exception>
#include <stack>
#include <mutex>
#include <memory>

struct empty_stack: std::exception {
    const char* what() const throw() {
        return "empty stack";
    }
};

// stack还不太理解
// 1. 可能存在死锁(拷贝构造的时候)
//      copy_assign 可能会发生死锁 需要注意锁的顺序
//      move_ctor/assign   对象无效 多线程也就没有意义了
// 2. mutex 不保证构造和析构函数
template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data=other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    // pass-by-copy
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        // new_value is a copy, just move it
        // @NOTE std::stack exception-safe
        data.push(std::move(new_value));
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(
            //@NOTE  std::move = &&
            // std::stack.top()  ==  &
            //  && & = &
            // so, still a lvalue reference
            std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        value=std::move(data.top());
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

