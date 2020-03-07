#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

// 可以考虑unique_ptr进行精简

// value-based
class mystr {
private:
    char* p_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void resize_if_needed(size_t extral) {
        size_t total_bytes = extral + size_;
        if (total_bytes <= capacity_) return;

        if (p_ == nullptr) {
            capacity_ = std::max(static_cast<size_t>(16), total_bytes);
            p_ = new char[capacity_];
        } else {
            capacity_ = std::max((2*capacity_), total_bytes);
            auto newplace = new char[capacity_];
            ::memcpy(newplace, p_, size_);
            delete [] p_;
            p_ = newplace;
        }
    }

    void swap(mystr& rhs) {
        using std::swap;
        swap(p_, rhs.p_);
        swap(size_, rhs.size_);
        swap(capacity_, rhs.capacity_);
    }

public:
    // mystr() {}
    explicit mystr(const char* c) {
        if (c) {
            size_ = ::strlen(c);
            resize_if_needed(size_);
        }
    }

    // free the resource (delete 会检查 p == nullptr)
    ~mystr() { /*if(p_)*/ delete [] p_; }

    // https://www.zhihu.com/question/29605575
    // 一个类的成员函数可以访问这个类的私有变量
    // 类定义的过程中 可以直接访问私有变量 同一个类可以访问私有成员
    // void test(mystr rhs) { return rhs.size };
    //
    // copy resource
    mystr(const mystr& rhs) {
        p_ = new char[rhs.capacity_];
        size_ = rhs.size_;
        ::memcpy(p_, rhs.p_, rhs.size_);
    }

    // transfer ownership of resource
    mystr(mystr&& rhs) {
        p_ = std::move(rhs.p_); rhs.p_ = nullptr;
        size_ = std::move(rhs.size_); rhs.size_ = 0;
    }

    // move/copy
    // free the old resource copy/move rhs
    mystr& operator=(mystr rhs) {
        rhs.swap(*this);
        return *this;
    }

    friend void swap(mystr& a, mystr& b) { a.swap(b); }

public:
    void append(char* c) { if (c) append(c, ::strlen(c)); }
    void append(const char* c) { if (c) append(c, ::strlen(c)); }

    void append(const char* c, size_t len) {
        if (len == 0) return;
        resize_if_needed(len);
        ::memcpy(p_+size_, c, len);
        size_ += len;
    }

    // no bound check
    char& operator[](size_t idx) {
        // assert(idx < capacity_);
        return *(p_ + idx);
    }

};

int main(int argc, char *argv[]) {
    char a[] = "hello";
    mystr s;
    s.append(a);
    mystr r = s;
    cout << r[0] << endl;

    mystr c;
    r = std::move(c);

    int *p = nullptr;
    delete p;

    return 0;
}