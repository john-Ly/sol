#ifndef LIST_H
#define LIST_H

#include <algorithm>
using namespace std;

/*
In considering the design, we will need to provide four classes:
1. The List class itself, which contains links to both ends, the size of the list, and a host
of methods.
2. The Node class, which is likely to be a private nested class. A node contains the data
and pointers to the previous and next nodes, along with appropriate constructors.
3. The const_iterator class, which abstracts the notion of a position, and is a pub-
lic nested class. The const_iterator stores a pointer to “current” node, and provides
implementation of the basic iterator operations, all in the form of overloaded operators
such as = , == , != , and ++ .
4. The iterator class, which abstracts the notion of a position, and is a public nested
class. The iterator has the same functionality as const_iterator , except that operator*
returns a reference to the item being viewed, rather than a constant reference to
the item. An important technical issue is that an iterator can be used in any rou-
tine that requires a const_iterator , but not vice versa. In other words, iterator IS-A
const_iterator .
*/

template <typename Object>
class List
{
  private:    
    // The basic doubly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node
    {
        Object  data;
        Node   *prev;
        Node   *next;

        Node( const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr )
          : data{ d }, prev{ p }, next{ n } { }
        
        Node( Object && d, Node * p = nullptr, Node * n = nullptr )
          : data{ std::move( d ) }, prev{ p }, next{ n } { }
    };

  public:
    class const_iterator
    {
      public:
  
        // Public constructor for const_iterator.
        const_iterator( ) : current{ nullptr }
          { }

        // Return the object stored at the current position.
        // For const_iterator, this is an accessor with a
        // const reference return type.
        const Object & operator* ( ) const
          { return retrieve( ); }
        
        const_iterator & operator++ ( )
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++ ( int )
        {
            const_iterator old = *this;
            ++( *this );
            return old;
        }

        const_iterator & operator-- ( )
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator-- ( int )
        {
            const_iterator old = *this;
            --( *this );
            return old;
        }
            
        bool operator== ( const const_iterator & rhs ) const
          { return current == rhs.current; }

        bool operator!= ( const const_iterator & rhs ) const
          { return !( *this == rhs ); }

      protected:
        Node *current;

        // Protected helper in const_iterator that returns the object
        // stored at the current position. Can be called by all
        // three versions of operator* without any type conversions.
        Object & retrieve( ) const
          { return current->data; }

        // Protected constructor for const_iterator.
        // Expects a pointer that represents the current position.
        const_iterator( Node *p ) :  current{ p }
          { }
        
        friend class List<Object>;
    };

    class iterator : public const_iterator
    {
      public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator( )
          { }

        Object & operator* ( )
          { return const_iterator::retrieve( ); }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object & operator* ( ) const
          { return const_iterator::operator*( ); }
        
        iterator & operator++ ( )
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }

        iterator & operator-- ( )
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }

      protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator( Node *p ) : const_iterator{ p }
          { }

        friend class List<Object>;
    };

  public:
    List( )
      { init( ); }

    ~List( )
    {
        clear( );
        delete head;
        delete tail;
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
      : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
   
    List & operator= ( List && rhs )
    {    
        std::swap( theSize, rhs.theSize );
        std::swap( head, rhs.head );
        std::swap( tail, rhs.tail );
        
        return *this;
    }
    
    // Return iterator representing beginning of list.
    // Mutator version is first, then accessor version.
    iterator begin( )
      { return iterator( head->next ); }

    const_iterator begin( ) const
      { return const_iterator( head->next ); }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end( )
      { return iterator( tail ); }

    const_iterator end( ) const
      { return const_iterator( tail ); }

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
 
    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    Object & front( )
      { return *begin( ); }

    const Object & front( ) const
      { return *begin( ); }

    Object & back( )
      { return *--end( ); }

    const Object & back( ) const
      { return *--end( ); }

    void push_front( const Object & x )
      { insert( begin( ), x ); }

    void push_back( const Object & x )
      { insert( end( ), x ); }

    void push_front( Object && x )
      { insert( begin( ), std::move( x ) ); }

    void push_back( Object && x )
      { insert( end( ), std::move( x ) ); }

    void pop_front( )
      { erase( begin( ) ); }

    void pop_back( )
      { erase( --end( ) ); }

    // Insert x before itr.
    iterator insert( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        ++theSize;
        return iterator( p->prev = p->prev->next = new Node{ x, p->prev, p } );
    }

    // Insert x before itr.
    iterator insert( iterator itr, Object && x )
    {
        Node *p = itr.current;
        ++theSize;
        /*
        Node* newNode = new Node{ std::move( x ), p->prev, p };
        p->prev->next = newNode; 
        p->prev = newNode;
        return iterator( p->prev );
        */
        return iterator( p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } );
    }
    
    // Erase item at itr.
    iterator erase( iterator itr )
    {
        Node *p = itr.current;
        iterator retVal( p->next );
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --theSize;

        return retVal;
    }

    iterator erase( iterator from, iterator to )
    {
        for( iterator itr = from; itr != to; )
            itr = erase( itr );

        return to;
    }

    // Operations:
    void reverse()
    {
        if(this->empty()) { std::cout << "This doubly linked list is empty!\n"; return; }
        if(this->size() == 1) { std::cout << "This doubly linked list has only one element!\n"; return ; }
        
        /*
        //// method 1: create a new list--------not only wastes memory, but also wastes processing power
        List *copyList = new List();
        // Start from the latest node
        Node *start = this->Tail;

        // Traverse until the first node is found
        while (start != nullptr)
        {
            copyList->push_back (start->data);
            start = start->prev;
        }

        this = copyList;
        */

        //// method 2: swap linked list node objects (references to the data)
        Node *firNode = this->head;
        Node *secNode = this->tail;
        for (int i=0; i <= this->size() / 2; i++)
        {
            std::swap(firNode->data, secNode->data);

            firNode = firNode->next;
            secNode = secNode->prev;
        }

        //// method 3: the head of the linked list will point to the last node of the linked list. 
        //// Also, each node’s “Next” and “Previous” properties need to be swapped too.
        Node *start = this->head;
        Node *temp = nullptr;

        // ------------------------------------------------------------
        // Loop through until null node (next node of the latest node) is found
        // ------------------------------------------------------------

        while (start != null)
        {
            // Swap the “Next” and “Previous” node properties
            temp = start->next;
            start->next = start->prev;
            start->prev = temp;

        // ------------------------------------------------------------
        // Head property needs to point to the latest node
        // ------------------------------------------------------------

        if (start.Previous == null)
        {
        linkedList.Head = start;
        }

        // ------------------------------------------------------------
        // Move on to the next node (since we just swapped 
        // “Next” and “Previous”
        // “Next” is actually the “Previous”
        // ------------------------------------------------------------

        start = start.Previous;
        }


    }

  private:
    int   theSize;
    Node *head;
    Node *tail;
	// Head points the start of the linked list 
	// tail points to the last node of the linked list.

    void init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#endif