#include <algorithm>

class List {
  private:
    struct Node {
        int  data;
        Node   *prev;
        Node   *next;

        Node(int d, Node* p = nullptr, Node* n = nullptr )
            : data(d), prev{p}, next{n} { }
    };

  private:
    int size_;
    Node* head;
    Node* tail;

    void init() {
        size_ = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

  public:
    List() { init(); }
    ~List() {
        clear();
        delete head;
        delete tail;
    }

    List( const List & rhs ) {
        init();
        for (auto i(rhs.head->next); i != rhs.tail; i=i->next) {
            push_back(i->data);
        }
    }

    List( List && rhs) : size_{ rhs.size_ }, head{ rhs.head }, tail{ rhs.tail } {
        rhs.size_ = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    List& operator=(List rhs) {
        rhs.swap(*this);
        return *this;
    }

    void swap(List& rhs) {
        using std::swap;
        swap(size_, rhs.size_);
        swap(head_, rhs.head_);
        swap(tail_, rhs.tail_);
    }

    // begin: head->next
    // end: tail
    int size( ) const { return size_; }
    bool empty( ) const { return size( ) == 0; }

    void clear() {
        while(!empty())
            pop_front( );
    }

    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    int& front() { return *(head->next); }
    int& back() { return *(tail->prev); }

    void push_front(int x) { insert(head->next, std::move(x)); }
    void push_back(int x) { insert(tail, std::move(x)); }
    void pop_front() { erase(head->next); }
    void pop_back() { erase(tail->prev); }

    // Insert x before cur.
    void insert(Node* cur, int x) {
        auto newNode = new Node{x, cur->prev, cur};
        if (!newNode) return;
        cur->prev->next = newNode;
        cur->prev = newNode;
        ++size_;
    }

    // Erase item at cur.
    void erase(Node* p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --size_;
    }

};