#include <algorithm>
#include <iostream>
#include <utility>       // std::exchange()
#include <cassert>
#include <array>
#include <queue>
#include <string>
#include <iomanip>

// @TODO 为什么测试结果显示 avl由优于llrb

namespace avl {
// @TODO 如何实现upper_bound + lower_bound
// 范围查找

// 这种bst 严格说是 set; (key == value)
// map的实现要分清楚 key_type value_type

// avl 和 bst十分相似 除了添加了balance()

using std::cout;
using std::ostream;
using std::endl;
template <typename Comparable>
class AvlTree {
  public:
    AvlTree( ) : root{ nullptr } { }

    // copy ctor
    AvlTree( const AvlTree & rhs )
        : root{ nullptr }
    { root = clone( rhs.root ); }

    // move ctor
    AvlTree( AvlTree && rhs )
        : root{ rhs.root }   // : root{std::exchange(rhs.root, nullptr)} { }
    { rhs.root = nullptr; }

    ~AvlTree() { makeEmpty( ); }

    AvlTree & operator=(AvlTree rhs) {
        rhs.swap(*this);
        return *this;
    }

    void swap(AvlTree& rhs) {
        using std::swap;
        swap(root, rhs.root);
    }

    friend void swap(AvlTree& lhs, AvlTree& rhs) { lhs.swap(rhs); }

    // Find the smallest/largest item in the tree.
    const Comparable& findMin( ) const {
        assert(!isEmpty());
        return findMin( root )->element;
    }
    const Comparable& findMax( ) const {
        assert(!isEmpty());
        return findMax( root )->element;
    }

    bool contains(const Comparable& x) const { return contains( x, root ); }
    bool isEmpty( ) const { return root == nullptr; }

    void printTree (ostream & out = cout) const {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    void makeEmpty( ) { makeEmpty(root); }
    void insert(Comparable x) { insert( std::move(x), root ); }
    void remove( const Comparable & x ) { remove( x, root ); }

  private:
    struct AvlNode {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;
        // height of node = number of edges in longest path from root to a leaf node.
        // height of tree = height of root = max depth
        // height of tree with 1 node = 0
        // h of empty tree = -1;

        // depth of node = number of edges in path from root to that node

        // depth = distance from root
        // height = distance from the longest leaf

        AvlNode(Comparable theElement, AvlNode *lt = nullptr, AvlNode *rt = nullptr, int h = 0)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{h} { }
    };

    AvlNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     *
     * @TODO how to deal with duplication
     * (1. add extral field - frequce - in AvlNode
     *  2. using linked list/ another search tree )
     */
    void insert(Comparable x, AvlNode * & t ) {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing

        balance( t );
    }

    void remove( const Comparable & x, AvlNode * & t) {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
        	// find the minimum of the right subtree OR maximun of the left subtree
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else   // one child + no children
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }

        balance( t );
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance(AvlNode * & t) {
        if( t == nullptr )
            return;

        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );

        t->height = std::max( height( t->left ), height( t->right ) ) + 1;
    }

    AvlNode * findMin( AvlNode *t ) const {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    AvlNode * findMax( AvlNode *t ) const {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    bool contains( const Comparable & x, AvlNode *t ) const {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    // post-order
    void makeEmpty( AvlNode * & t) {
        if(t != nullptr) {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    // inorder print
    void printTree( AvlNode *t, ostream & out ) const {
        if( t != nullptr ) {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    // deep copy
    AvlNode * clone( AvlNode *t ) const {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ) };
    }

    // Avl manipulations
    int height( AvlNode *t ) const { return t == nullptr ? -1 : t->height; }

    // 先保存旧值, 在更新
    void rotateWithLeftChild( AvlNode * & k2 ) {
        using std::max;
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild( AvlNode * & k1 ) {
        using std::max;
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 ) {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 ) {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

};

}

namespace llrb {
using std::cout;
using std::ostream;
using std::endl;
template <typename Comparable>
class RedBlackTree {
  public:
    RedBlackTree() : root(nullptr) {}
    RedBlackTree(const RedBlackTree & rhs) { root = clone( rhs.root ); }
    RedBlackTree(RedBlackTree&& rhs) : root{std::exchange(rhs.root, nullptr)} {}
    RedBlackTree & operator=(RedBlackTree rhs) { rhs.swap(*this); return *this; }
    ~RedBlackTree() { makeEmpty(); }

    void swap(RedBlackTree& rhs) { std::swap(root, rhs.root); }
    friend void swap(RedBlackTree& lhs, RedBlackTree& rhs) { lhs.swap(rhs); }

    const Comparable& findMin( ) const {
        assert(!isEmpty());
        return findMin(root)->element;
    }
    const Comparable& findMax( ) const {
        assert(!isEmpty());
        return findMax(root)->element;
    }
    void deleteMin() {
        assert(!isEmpty());
        deleteMin(root);

        if (root != nullptr)
            root->color = BLACK;
    }
    void deleteMax() {
        assert(!isEmpty());
        deleteMax(root);

        if (root != nullptr)
            root->color = BLACK;
    }

    bool contains(const Comparable& x) const { return contains( x, root ); }
    bool isEmpty( ) const { return root == nullptr; }
    void printTree (ostream & out = cout) const {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    void makeEmpty( ) { makeEmpty(root); }
    void insert(Comparable x) {
        insert(std::move(x), root );
        // insert imply that  "root != nullptr"
        root->color = BLACK;
    }
    void remove(const Comparable& x) {
        remove(x, root);

        if (root != nullptr)
            root->color = BLACK;
    }

  private:
    enum { RED, BLACK };
    struct RedBlackNode {
        Comparable    element;
        int           color;
        RedBlackNode *left;
        RedBlackNode *right;
        int           height;

        RedBlackNode(Comparable theElement, int c,
                     RedBlackNode *lt = nullptr,
                     RedBlackNode *rt = nullptr,
                     int h = 0)
        : element{std::move(theElement)}, color{c}, left{lt}, right{rt}, height{h} {}
    };

    RedBlackNode* root;   // The tree header (contains negInf)

    bool contains(const Comparable& x, RedBlackNode *t) const {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    RedBlackNode* findMin(RedBlackNode* t) const {
        // recursive: base case
        // if( t == nullptr ) return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin(t->left);
    }
    RedBlackNode* findMax(RedBlackNode* t) const {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    bool isRed(RedBlackNode* t) const {
        if (t == nullptr) return false;
        return (t->color == RED);
    }

    void insert(Comparable x, RedBlackNode*& t) {
        // 1. Insert a new node at the bottom. (will be 3/4-node)
        if(t == nullptr)
            t = new RedBlackNode{std::move(x), RED};

        if( x < t->element )
            insert(std::move(x), t->left);
        else if( t->element < x )
            insert(std::move(x), t->right);
        else
            ;  // Duplicate; do nothing

        fixUp(t);

        adjuHeight(t);
    }


    // Invariant: h or one of its children is RED
    // • search path goes left: use moveRedDownLeftChild().
    // • search path goes right: use moveRedDownRightChild().
    // • delete node at bottom
    // • fix right-leaning reds on the way up
    void remove(const Comparable& x, RedBlackNode*& t) {
        // left.path
        if(x < t->element) {
            // @BUG delete element < min
            if (t->left == nullptr) return;
            if (!isRed(t->left) &&
                !isRed(t->left->left)) {
                moveRedDownLeftChild(t);
            }
            remove(x, t->left);
        } else {
            if (isRed(t->left)) { rotateWithLeftChild(t); }
            // equal(at bottom) delete node
            if (x == t->element && t->right == nullptr) {
                delete t;
                t = nullptr;
                return;
            }

            if (t->right == nullptr) return;
            if (!isRed(t->right) && !isRed(t->right->left)) { moveRedDownRightChild(t); }
            // equal(NOT at bottom) delete node
            if (x == t->element) {
                t->element = findMin(t->right)->element;
                deleteMin(t->right);
            } else { // right.path
                remove(x, t->right);
            }
        }

        fixUp(t);
    }

    // Delete strategy (works for 2-3 and 2-3-4 trees)
    // invariant: current node is not a 2-node
    // 1. If search ends in a 3/4-node, just remove it.
    // 2. Removing a 2-node would destroy balance

    // 递归函数代表两个阶段的分界点(递归函数之前 上一个阶段的工作; 递归函数之后 下一个阶段的工作)
    // 删除操作(递归)
    // 1. top-down 查找要删除的节点(需要变换树的结构 -> 保证当前节点(包含待删除元素)不是 2-node 节点
    // 2. bottom-up 递归到最深处的时候会进行回溯 这个过程会进行 fixUp, 重新保证树的'平衡'(RB 理论上2-3 tree 完全平衡)
    void deleteMin(RedBlackNode*& t) {
        // cout << char(t->element - 1 + 'A') << '\n';
        if (t->left == nullptr) { delete t; t = nullptr; return; }

        // 连续两个节点都是BLACK, 说明需要调整树结构 转化为3/4-node
        if (!isRed(t->left) && !isRed(t->left->left)) { moveRedDownLeftChild(t); }

        deleteMin(t->left);

        // colorFlip() 在递归函数之前还是i递归函数之后 影响的是树的定义(这种实现应该不是红黑树 而是变种)
        fixUp(t);
    }

    // invariant: h/ h.right is RED  => deletion easy at bottom
    void deleteMax(RedBlackNode*& t) {
        // lean 3-nodes to the right(因为是左倾, 删除最大值需要找到最右节点 所以向右旋转 能够方便删除)
        if (isRed(t->left)) rotateWithLeftChild(t);

        // remove node on bottom level
        // t must be RED by invariant
        if (t->right == nullptr) { delete t; t = nullptr; return; }

        // borrow from sibling if necessary
        if (!isRed(t->right) && !isRed(t->right->left)) { moveRedDownRightChild(t); }

        deleteMax(t->right);

        // fixUp 因为是递归的回溯阶段
        fixUp(t);
    }

    // @TODO 触发条件 不太理解(直觉上能猜，不完全明白)
    void moveRedDownLeftChild(RedBlackNode*& h) {
        // Assuming that h is red and both h.left and h.left.left
        // are black, make h.left or one of its children red.

        // case-1: h.right.left is BLACK
        // case-2: h.right.left is RED
        colorFlip(h);
        if (isRed(h->right->left)) {
            // h->right->left RED ---> borrow from sibling
            rotateWithLeftChild(h->right);
            rotateWithRightChild(h);
            colorFlip(h);
        }
    }

    void moveRedDownRightChild(RedBlackNode*& h) {
        // Assuming that h is red and both h.right and h.right.left
        // are black, make h.right or one of its children red.
        colorFlip(h);
        if (isRed(h->left->left)) {
            rotateWithLeftChild(h);
            colorFlip(h);
        }
    }

    // 1. Color flips and rotations preserve perfect black-link balance.
    // 2. Fix right-leaning reds and eliminate 4-nodes on the way up.
    void fixUp(RedBlackNode*& t) {
        // Lesson learned from insert() !!!

        // Enforce left-leaning condition.
        if (isRed(t->right)) { rotateWithRightChild(t); }

        // Balance a 4-node.
        if (isRed(t->left) && isRed(t->left->left)) { rotateWithLeftChild(t); }

        // @TODO 父节点和两个子节点应该不同的颜色
        // Split a 4-node.
        if (isRed(t->left) && isRed(t->right)) { colorFlip(t); }
    }

    int height(RedBlackNode* t) const { return t == nullptr ? -1 : t->height; }

    void adjuHeight(RedBlackNode*& h) { h->height = std::max(height(h->left), height(h->right)) + 1; }

    void colorFlip(RedBlackNode*& h) {
        h->color =  (h->color == RED ? BLACK : RED);
        h->left->color = (h->left->color == RED ? BLACK : RED);
        h->right->color = (h->right->color == RED ? BLACK : RED);
    }

    void rotateWithLeftChild(RedBlackNode*& k2) {
        RedBlackNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        adjuHeight(k2);
        adjuHeight(k1);
        k2 = k1;
        std::swap(k2->color, k2->right->color);
    }

    void rotateWithRightChild(RedBlackNode*& k1) {
        RedBlackNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        adjuHeight(k1);
        adjuHeight(k2);
        k1 = k2;
        std::swap(k1->color, k1->left->color);
    }

    // post-order
    void makeEmpty(RedBlackNode*& t) {
        if(t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    // level order
    void printTree(RedBlackNode *t, ostream& out) const {
        if (t == nullptr) return;
        std::queue<RedBlackNode*> Q;
        Q.push(t);
        while(!Q.empty()) {
            for(auto i=Q.size(); i>0; --i) {
                auto cur = Q.front(); Q.pop();
                std::string s;
                if(cur->left) {
                    s += "<-";
                    Q.push(cur->left);
                }
                s += ':'; s += std::to_string(height(cur));
                s += ':'; s += (cur->element - 1 + 'A');
                if (isRed(cur)) s += '*';
                s += ':';
                if(cur->right) {
                    s += "->";
                    Q.push(cur->right);
                }
                out << s << std::setw(12) << std::left;
            }
            cout << endl;
        }
    }

    RedBlackNode* clone(RedBlackNode* t) const {
        if( t == nullptr )  // Cannot test against nullNode!!!
            return nullptr;
        else
            return new RedBlackNode{t->element, t->color,
                                    clone( t->left ), clone( t->right )};
    }
};

}

void testAVL(int N) {
    using namespace avl;
    AvlTree<int> t;
    int NUMS = N;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );
    t.remove( 0 );
    for( i = 1; i < NUMS; i += 2 )
        t.remove( i );

    if( NUMS < 40 )
        t.printTree( );
    if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    // for( i = 2; i < NUMS; i += 2 )
    //     if( !t.contains( i ) )
    //         cout << "Find error1!" << endl;

    // for( i = 1; i < NUMS; i += 2) {
    //     if( t.contains( i )  )
    //         cout << "Find error2!" << endl;
    // }

    // AvlTree<int> t2;
    // t2 = t;

    // for( i = 2; i < NUMS; i += 2 )
    //     if( !t2.contains( i ) )
    //         cout << "Find error1!" << endl;

    // for( i = 1; i < NUMS; i += 2) {
    //     if( t2.contains( i ) )
    //         cout << "Find error2!" << endl;
    // }

    cout << "End of test..." << endl;
}

void testLLRB() {
    using namespace llrb;
    RedBlackTree<int> t;
    int NUMS = 39;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );

    if( NUMS < 40 )
        t.printTree( );
    if( t.findMin( ) != 1 || t.findMax( ) != NUMS - 1 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 1; i < NUMS; ++i )
        if( !t.contains( i ) )
            cout << "Find error1!" << endl;
    if( t.contains( 0 ) )
        cout << "Oops!" << endl;


    RedBlackTree<int> t2 = t;

    for( i = 1; i < NUMS; ++i )
        if( !t2.contains( i ) )
            cout << "Find error1!" << endl;
    if( t2.contains( 0 ) )
        cout << "Oops!" << endl;

    cout << "Test complete..." << endl;
}

// RedBlack not in perfect balance, actually.
void testRedLink() {
    using namespace llrb;
    RedBlackTree<int> t;

    // test_insert
    // std::array<char, 10> sym = {'A', 'S', 'E', 'R', 'C', 'D', 'I', 'N', 'B', 'X'};
    // for (auto c : sym)
    //     t.insert(c-'A'+1);

    // test_deleteMin
    // insert A-O
    for (int i=1; i<=15; ++i)
        t.insert(i);

    // t.printTree( );
    // cout << (char)(t.findMin() - 1 + 'A') << '\n';
    t.deleteMax();
    t.printTree( );
    cout << endl;
    t.deleteMax();
    t.printTree( );
    // cout << (char)(t.findMin() - 1 + 'A') << '\n';
}

void testDelete1() {
    using namespace llrb;
    RedBlackTree<int> t;

    // insert A-O
    for (int i=1; i<=15; ++i)
        t.insert(i);

    t.printTree( );
    // 1. delete the element that does not exist
    t.remove(0);
    t.remove(16);

    t.insert(17);
    t.remove(16);
    // 2. delete all element
    for (int i=1; i<=15; ++i)
        t.remove(i);

    t.printTree( );
}

void testDelete2(int N) {
    using namespace llrb;
    RedBlackTree<int> t;
    int NUMS = N;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );
    t.remove( 0 );
    for( i = 1; i < NUMS; i += 2 )
        t.remove( i );

    if( NUMS < 40 )
        t.printTree( );
    if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    // for( i = 2; i < NUMS; i += 2 )
    //     if( !t.contains( i ) )
    //         cout << "Find error1!" << endl;

    // for( i = 1; i < NUMS; i += 2) {
    //     if( t.contains( i )  )
    //         cout << "Find error2!" << endl;
    // }

    // RedBlackTree<int> t2;
    // t2 = t;

    // for( i = 2; i < NUMS; i += 2 )
    //     if( !t2.contains( i ) )
    //         cout << "Find error1!" << endl;

    // for( i = 1; i < NUMS; i += 2) {
    //     if( t2.contains( i ) )
    //         cout << "Find error2!" << endl;
    // }

    cout << "End of test..." << endl;
}

int main( ) {
    int N, op;
    std::cout << "Input N & op: {N=400,0000 op=1(avl)/2(llrb)}\n";
    std::cin >> N >> op;
    if (op == 1)
        testAVL(N);
    else if (op == 2)
        testDelete2(N);

    // testLLRB();
    // testRedLink();
    // testDelete1();
    return 0;
}
