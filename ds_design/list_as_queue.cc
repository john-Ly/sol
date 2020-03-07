#include <memory>
#include <mutex>
#include <condition_variable>
using std::shared_ptr;
using std::unique_ptr;
using std::mutex;

// 在链表中应该用哪种智能指针比较合理？ - 知乎
// https://www.zhihu.com/question/40265434/answer/85683381

// 使用单链表 实现队列
// tail -> 入队
// head -> 出队
namespace ver_1 {
    template<typename T>
    class queue {
    private:
        struct node {
            T data;
            std::unique_ptr<node> next;

            node(T data_): data(std::move(data_)) {}
        };

        std::unique_ptr<node> head;  // 1
        node* tail;  // 2

    public:
        queue() {}
        queue(const queue& other)=delete;
        queue& operator=(const queue& other)=delete;

        std::shared_ptr<T> try_pop() {
            if(!head) {
                return std::shared_ptr<T>();
            }
            std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));

            // 移交第一个元素的所有权
            std::unique_ptr<node> const old_head=std::move(head);
            head=std::move(old_head->next);  // 3

            return res;
        }

        // 并发度不够 同时操作head和tail
        void push(T new_value) {
            std::unique_ptr<node> p(new node(std::move(new_value)));
            node* const new_tail = p.get();
            if(tail) {
                tail->next=std::move(p);  // 4 所有权转移
            }
            else {
                head=std::move(p);  // 5
            }
            tail=new_tail;  // 6
        }
    };
}

// 虚拟节点意味着try_pop()和push()不能对同一节点进行操作，所以就不再需要互斥了
namespace ver_2 {
    template<typename T>
    class queue {
    private:
        struct node {
            std::shared_ptr<T> data;
            std::unique_ptr<node> next;
        };

        std::unique_ptr<node> head;
        node* tail;

    public:
        queue(): head(new node),tail(head.get()) {}

        queue(const queue& other)=delete;
        queue& operator=(const queue& other)=delete;

        std::shared_ptr<T> try_pop() {
            if(head.get()==tail) {
                return std::shared_ptr<T>();
            }
            std::shared_ptr<T> const res(head->data);
            std::unique_ptr<node> const old_head=std::move(head);
            head=std::move(old_head->next);
            return res;
        }

        void push(T new_value) {
            std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
            std::unique_ptr<node> p(new node);
            tail->data=new_data;
            node* const new_tail=p.get();
            tail->next=std::move(p);
            tail=new_tail;
        }
    };

}

// 前两个版本是单线程版本

// - tail->next == nullptr
// - tail->data == nullptr
// - head.get() == tail(意味着空列表)
// - 单元素列表 head->next = tail
// - 列表中的每一个节点x，x!=tail且x->data指向一个T类型的实例，并且x->next指向列表中下一个节点。
//    x->next == tail意味着x就是列表中最后一个节点
// - 顺着head的next节点找下去，最终会找到tail
namespace ver_mutex {
    template<typename T>
    class threadsafe_queue {
    private:
        struct node {
            shared_ptr<T> data;
            unique_ptr<node> next;
        };

        mutex head_mutex;
        unique_ptr<node> head;
        mutex tail_mutex;
        node* tail;

        node* get_tail() {
            std::lock_guard<mutex> tail_lock(tail_mutex);
            return tail;
        }

        // 单线程 去除头结点
        unique_ptr<node> pop_head() {
            unique_ptr<node> old_head = std::move(head);
            head = std::move(old_head->next);
            return old_head;
        }

        // 锁的传递
        std::unique_lock<mutex> wait_for_data(){
            std::unique_lock<mutex> head_lock(head_mutex);
            data_cond.wait(head_lock, [&]{return head.get()!=get_tail();});
            return std::move(head_lock);
        }

        unique_ptr<node> wait_pop_head() {
            std::unique_lock<mutex> head_lock(wait_for_data());  // 4
            return pop_head();
        }

        unique_ptr<node> wait_pop_head(T& value) {
            std::unique_lock<mutex> head_lock(wait_for_data());  // 5
            value=std::move(*head->data);
            return pop_head();
        }

        unique_ptr<node> try_pop_head() {
            std::lock_guard<mutex> head_lock(head_mutex);
            if(head.get()==get_tail()) {
                return unique_ptr<node>();
            }
            return pop_head();
        }

        unique_ptr<node> try_pop_head(T& value) {
            std::lock_guard<mutex> head_lock(head_mutex);
            if(head.get()==get_tail()) {
                return unique_ptr<node>();
            }
            value = std::move(*head->data);
            return pop_head();
        }

    public:
        threadsafe_queue(): head(new node),tail(head.get()) {}
        threadsafe_queue(const threadsafe_queue& other)=delete;
        threadsafe_queue& operator=(const threadsafe_queue& other)=delete;
        shared_ptr<T> try_pop() {
            unique_ptr<node> old_head=pop_head();
        }

        void push(T new_value) {
            shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
            unique_ptr<node> p(new node);
            {
                std::lock_guard<mutex> tail_lock(tail_mutex);
                tail->data=new_data;
                node* const new_tail=p.get();
                tail->next=std::move(p);
                tail=new_tail;
            }
            data_cond.notify_one();
        }

        shared_ptr<T> wait_and_pop() {
            unique_ptr<node> const old_head=wait_pop_head();
            return old_head->data;
        }

        void wait_and_pop(T& value) {
            unique_ptr<node> const old_head = wait_pop_head(value);
        }

        shared_ptr<T> try_pop() {
            unique_ptr<node> old_head = try_pop_head();
            return old_head ? old_head->data : shared_ptr<T>();
        }

        bool try_pop(T& value) {
            unique_ptr<node> const old_head=try_pop_head(value);
            return old_head;
        }

        bool empty() {
            // @TODO why get head mutex first
            std::lock_guard<mutex> head_lock(head_mutex);
            return (head.get()==get_tail());
        }

    };
}
