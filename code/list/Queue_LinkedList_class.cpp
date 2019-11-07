#include <algorithm>
using namespace std;

template <typename Object>
class Queue
{
  private:
    struct Node
    {
        Object  data;
        Node   *next;

        Node( const Object & d = Object{ }, Node * n = nullptr )
          : data{ d }, next{ n } { }
        
        Node( Object && d, Node * n = nullptr )
          : data{ std::move( d ) }, next{ n } { }
    };

  public:
    Queue( ) : front(nullptr), rear(nullptr)
      { }

    ~Queue( )
    {
        delete front;
        delete rear;
    }
    
    void EnQueue(Object x)
	{
		Node *temp = new Node(x);
		if(front == nullptr && rear == nullptr){
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp;
	}

	void DeQueue() 
	{
		Node *temp = front;
		if(front == nullptr) {
			printf("Queue is Empty\n");
			return;
		}
		if(front == rear)
			front = rear = nullptr;
		else
			front = front->next;
			
		delete temp;
		temp = nullptr;
	}
	
	Object Front() {
		if(front == nullptr) {
			printf("Queue is empty\n");
			return;
		}
		return front->data;
	}

  private:
    Node *front;
    Node *rear;
};
