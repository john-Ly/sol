#include <iostream>
#include <string>
#include <cassert>
using namespace std;

template <class T>
class Stack {
private:
	T* elements;   // 堆栈名
	int top;       // 栈顶指针的位置
	int size;      // 堆栈的大小

public: //Constructor-Destructor
	enum {DefaultStack = 50, EmptyStack = -1};
	Stack(){
		size = DefaultStack;
		allocate();
	}

	Stack(int s) {
		if(s<0) s *= -1;
		else if (0==s) s = DefaultStack;
		size = s;
		allocate();
	}

	Stack( const Stack & rhs )
	  : size{rhs.size}, top{rhs.top}, elements{nullptr}
	{
		elements = new T[size];
        for( int k = 0; k < size; ++k )
            elements[ k ] = rhs.elements[ k ];
	}

	Stack( Stack && rhs )
	  : size{rhs.size}, top{rhs.top}, elements{rhs.elements}
	{
		rhs.elements = nullptr;
        rhs.size = 0;
        rhs.top = EmptyStack;
    }

	// swap　avoid copy from itself  a[i] = a[j]
	Stack & operator= ( const Stack & rhs )
    {
        Stack copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

	Stack & operator= ( Stack && rhs )
    {
		std::swap( size, rhs.size );
        std::swap( top, rhs.top );
        std::swap( elements, rhs.elements );
        return *this;
    }

	~Stack() {
		delete[] elements;
	}

public:
	void push(const T& e){
		if(!full()) elements[++top] = e;  // 栈的实现纯粹是数组  因此top只是形式上的
		else cout << "Stack full!";
	}

	T pop() {
		if(!empty()) return elements[top--];
		else{
			cout << "Stack empty";
			return;
		}
	}

	T top() const {
		if(!empty()) return elements[top];
		else{
			cout << "Stack empty";
			return;
		}
	}

	bool empty() const {
		return top <= EmptyStack;
	}

	bool full() const {
		return top+1 >= size;
	}

private:
	void allocate() {
		elements = new T[size];
		top = EmptyStack;     // top == -1;
	}

	friend ostream& operator<<(ostream& os, const Stack<T>& s){
		s.msg("Stack contents:");
		int t = s.top;
		while (t > s.EmptyStack)
		cout << s.elements[t--] << endl;
		return os;
	}
};

int main(){
	Stack<string> s;
	string buf;
	int n;
	cout << "Input the numbers of string: " << endl;
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> buf;
		s.push(buf);
	}
	cout << "the content in stack:" << endl;
	for(int i=0; i<n; i++){
		cout << s.pop() << "--";
	}
	return 0;
}