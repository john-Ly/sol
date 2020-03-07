#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

// 无界 消息阻塞队列 生产者-消费者队列
template<typename T>
class msg_queue {
private:
    mutable std::mutex mut_;
    std::queue<T> queue_;
    std::condition_variable notEmpty_;
    std::condition_variable notFull_;
    int capacity_;
public:
    explicit msg_queue(int maxSize) : queue_(maxSize), capacity(maxSize) {}
    msg_queue(const msg_queue& rhs) = deleted;
    msg_queue& operator=(const msg_queue& rhs) = deleted;

    void push(T new_value) {
        std::unique_lock<std::mutex> lk(mut_);
        notFull_.wait(lk, [this]{ return queue_.size() < capacity_; });
        queue_.push(std::move(new_value));
        notEmpty_.notify_one(); // 1  只会唤醒一个线程
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut_);
        notEmpty_.wait(lk,[this]{return !queue_.empty();});
        value=std::move(queue_.front());
        queue_.pop();
        notFull_.notify_one(); // 1  只会唤醒一个线程
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut_);
        notEmpty_.wait(lk,[this]{return !queue_.empty();}); // 4
        // 如果make_shared抛出异常(内存不足) -> 其他线程还是在睡眠
        // @NOTE 在队列中存储shared_ptr
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(queue_.front())));
        queue_.pop();
        notFull_.notify_one(); // 1  只会唤醒一个线程

        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut_);
        if(queue_.empty())
            return false;
        value=std::move(queue_.front());
        queue_.pop();
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut_);
        if(queue_.empty())
            return std::shared_ptr<T>(); // 5
        std::shared_ptr<T> res(
            std::make_shared<T>(std::move(queue_.front())));
        queue_.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mut_);
        return queue_.empty();
    }

    bool full() const {
        std::lock_guard<std::mutex> lk(mut_);
        return queue_.size() >= capacity_;
    }


    size_t size() const {
        std::lock_guard<std::mutex> lk(mut_);
        return queue_.size();
    }

    size_t capcity() const {
        return capcity_;
    }

};
}

