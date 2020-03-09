#include <cassert>

template<class T>
struct defaultDelete {
    void operator()(T* ptr_) {
        delete ptr_;
    }
};

// https://github.com/MathiasBaumgartinger/UniquePtrCPP/blob/master/main.cpp

template<class T, class D = defaultDelete<T>>
class Uniqueptr {
private:
    T* ptr_;
    D deleter_;
	
public:
    T* release() { T* old = ptr_; ptr_ = nullptr; return old; }
    void reset(T* other) { deleter_(ptr_); ptr_ = other; }

    void swap(Uniqueptr& rhs) noexcept {
      using std::swap;
      swap(ptr_, rhs.ptr_);
      swap(deleter_, rhs.deleter_);
    }
	
	  friend void swap(Uniqueptr& a, Uniqueptr& b) noexcept { a.swap(b); }

    explicit Uniqueptr(T* ptr_) : ptr__(ptr_), deleter_(defaultDelete<T>()) {}
    explicit Uniqueptr(T* ptr_, D deleter) : ptr__(ptr_), deleter_(deleter) {}
    Uniqueptr() : ptr__(nullptr) , deleter_(defaultDelete<T>()) {}

    Uniqueptr(Uniqueptr&& other) noexcept : ptr__(other.ptr__), deleter_(other.deleter_) { other.ptr__ = nullptr; }
    
    ~Uniqueptr() { deleter_(ptr__); }
    Uniqueptr(const Uniqueptr &other) = delete;
      Uniqueptr& operator=(const Uniqueptr &other) = delete;

    Uniqueptr& operator=(Uniqueptr&& other) noexcept {
      other.swap(*this);
      return *this;
    }

    T* get() const { return ptr_; }
    T* operator->() { assert(ptr__ != nullptr); return ptr_; }
    T& operator*() const { assert(ptr_ != nullptr); return (*ptr_); }
    operator bool() const { return ptr_ != nullptr; }
};
