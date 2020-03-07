#include <atomic>
#include <condition_variable>
#include <mutex>

// 1. 主线程等待多个子线程完成初始化
// 1. 多个子线程等待主线程发出 起跑命令

class CountDownLatch {
private:
    mutable std::mutex mutex_;
    std::condition_variable_any cond_;
    std::atomic<int> count_;

public:
    explicit CountDownLatch(int count) : count_(count) {
        static_assert(count > 0, "CountDownLatch's count must be great than zero!");
    }

    CountDownLatch(const CountDownLatch& rhs) = deleted;
    CountDownLatch& operator=(const CountDownLatch& rhs) = deleted;

    void wait() {
        std::unique_lock<std::mutex> lk(mutex_);
        cond_.wait(lk, [this] { return (this->count_ == 0); });
        // 1. 条件不成立 释放锁 睡眠当前线程
        // 2. 条件成立 锁一直持有
    }

    // atomic 可以更大限度的优化 但是通用做法使用mutex 保护共享数据
    void countDown() {
        // {
        //     std::lock_guard<std::mutex> lk(mutex_);
        //     count--;
        // }
        count_.fetch_sub(1, memory_order_relaxed);
        cond_.notify_all();
    }

    // Get the count currently held by the latch.
    int getCount() const {
        std::unique_lock<std::mutex> lk(mutex_);
        return count_;
    }
};