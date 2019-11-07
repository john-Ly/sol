#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <algorithm>
using namespace std;

template <typename Object>
class List
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
    List( )
      { init( ); }

    ~List( )
    {
        clear( );
        delete head;
    }

    List( const List & rhs )
    {
        init( );
        for( auto & x : rhs )
            push_back( x );
    }

    List & operator= ( const List & rhs )
    {
        List copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    
    List( List && rhs )
      : theSize{ rhs.theSize }, head{ rhs.head }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
    }
   
    List & operator= ( List && rhs )
    {    
        std::swap( theSize, rhs.theSize );
        std::swap( head, rhs.head );
        
        return *this;
    }
    
    // Return number of elements currently in the list.
    int size( ) const
      { return theSize; }

    // Return true if the list is empty, false otherwise.
    bool empty( ) const
      { return size( ) == 0; }

    void clear( )
    {
        while( !empty( ) )
            pop_front( );
    }

    void push_front( const Object & x ) 
	{
		Node *newNode = new Node(x, head->next);
		head->next = newNode;
		++theSize;
	}
	  
	void push_front( Object && x )
	{
		Node *newNode = new Node( std::move( x ), head->next);
		head->next = newNode;
		++theSize;
	}
  
    void push_back( const Object & x )
	{
		if(head->next == nullptr) push_front(x);
		else {
			Node *tailNode = head;
			while (tailNode->next != nullptr) tailNode = tailNode->next;
			Node *newNode = new Node(x);
			tailNode->next = newNode;
			++theSize;
		}
	}

    void push_back( Object && x )
	{
		if(head->next == nullptr) push_front(x);
		else {
			Node *tailNode = head;
			while (tailNode->next != nullptr) tailNode = tailNode->next;
			Node *newNode = new Node(std::move( x ));
			tailNode->next = newNode;
			++theSize;
		}
	}

	// Insert x before itr.
    void insert( int position, const Object & x )
    {
		if(position == 1) push_front(x);
		else if(position == size()+1) push_back(x);
			
		// @TODO try catch
		else if(position > size()+1 || position < 1) std::cout << "\nINVALID POSITION\n";
        else {
			Node *currNode = head;
			while( (position-1)>0 ){
				currNode = currNode->next;
				position--;
			}
			Node *newNode = new Node(x, currNode->next);
			currNode->next = newNode;
			++theSize;
		}
    }
    
    Object pop_front( )
	{
		Object tmp = head->next.data;
		Node *p = head->next;
		head->next = head->next->next;
		delete p;
		p = nullptr;
		
		theSize--;
		return tmp;
	}

    Object pop_back( )
	{
		Node *currNode = head;
		while (currNode->next->next != nullptr) {
			currNode = currNode->next;
		}
		Object tmp = currNode->next.data;
		Node *p = currNode->next;
		currNode->next = nullptr;
		delete p;
		p = nullptr;
		
		theSize--;
		return tmp;
	}

    // Erase item at itr.
    Object erase( int position )
    {
		if (empty()) {
			std::cout << "\nList is empty!\n";
			return;
		} else {
			if(position == 1) return pop_front();
			else if(position == size()) return pop_back();
				
			// @TODO try catch
			else if(position > size() || position < 1) {
				std::cout << "\nINVALID POSITION\n";
				return;
			} else {
				Node *currNode = head;
				while( (position-1)>0 ){
					currNode = currNode->next;
					position--;
				}
				Object tmp = currNode->next.data;
				Node *p = currNode->next;
				currNode->next = currNode->next->next;;
				delete p;
				p = nullptr;
		
				theSize--;
				return tmp;
			}
		}
    }

    void erase( int from, int to )
    {
		Object dummy;
        for( int itr = from; itr != to; )
            dummy = erase( itr );
		
        return dummy;
    }

	void iterativePrint() 
	{
		// print in forward order
		if(empty()) return;
		Node *currNode = head;
		while (currNode->next != nullptr) {
			std::cout << "->" << currNode->next.data << " ";
			currNode = currNode->next;
		}
	}
	
	//// print elements of a linked list in forward and reverse order using recursion
	void recursivePrint() 
	{
		// print in forward order
		if(empty()) return;
		std::cout << "->" << head->next.data << " ";
		Print(head->next->next);
	}
	// for normal print, recursive approach is worst than iterative method.
	// iterative: only use one temporary var
	// recursive: many section of stack due to functions call

	void RversePrint() 
	{
		// print in reverse order
		if(empty()) return;
		RversePrint(head->next->next);
		std::cout << "->" << head->next.data << " ";
	}
	
	//// iterative method
	void iterativeReverse() 
	{
		if(empty()) { std::cout << "This singly linked list is empty!\n"; return; }
		if(size() == 1) { std::cout << "This singly linked list has only one element!\n"; return ; }
		Node *current, *prev, *next;
		current = head->next;
		prev = nullptr;
		
		while(current != nullptr)
		{
			next = current->next;  // store the next node
			current->next = prev;  // current point to prev
			
			prev = current;
			current = next;
		}
		head->next = prev;
	}
	
	void recusiveRverse() 
	{
		if(empty()) { std::cout << "This singly linked list is empty!\n"; return; }
		if(size() == 1) { std::cout << "This singly linked list has only one element!\n"; return ; }

		recursiveRverse(head->next->next);
		Node* q = head->next->next;
		q->next = head->next;
		head->next->next = nullptr;
	}

  private:
    int theSize;
    Node *head;

    void init( )
    {
        theSize = 0;
        head = new Node;
        head->next = nullptr;
    }
};

#endif