#include <iostream>
#include &quot;List.h&quot;
 
using namespace std;
 
// Circular linked list node class.
// Stores node contents and the pointer to next node.
template &lt;class T&gt;
class CLinkedListNode
{
public:
    T data;
    CLinkedListNode *next;
    CLinkedListNode(const T info, CLinkedListNode *nextValue = NULL)
    {
        data = info;
        next = nextValue;
    }
    CLinkedListNode(CLinkedListNode *nextValue = NULL)
    {
        next = nextValue;
    }
};
 
// Singly linked list class.
template &lt;class T&gt;
class CLinkedList : public List&lt;T&gt;
{
private:
    CLinkedListNode&lt;T&gt; *tail, *current;
 
public:
    CLinkedList();
    ~CLinkedList();
 
    // Check if list is empty.
    bool IsEmpty();
 
    // Appent item to the end of the list.
    void AppendToTail(T value);
 
    // Gets current node and changes current pointer to next node.
    T GetCurrentNode();
 
    // Print contents of the list.
    void Print();
};
 
template &lt;class T&gt;
CLinkedList&lt;T&gt;::CLinkedList()
{
    // Create empty list with tail pointing to NULL.
    tail = current = NULL;
}
 
template &lt;class T&gt;
CLinkedList&lt;T&gt;::~CLinkedList()
{
    if (IsEmpty())
    {
        return;
    }
 
    CLinkedListNode&lt;T&gt; *tmp = tail-&gt;next;
 
    // Go through each node until tail is reached.
    while (tmp != tail)
    {
        // Delete head node and repoint tail to new head.
        tail-&gt;next = tmp-&gt;next;
 
        // Delete current node.
        delete tmp;
 
        // Point tmp to new head node.
        tmp = tail-&gt;next;
    }
 
    // Delete tail.
    delete tmp;
}
 
template &lt;class T&gt;
bool CLinkedList&lt;T&gt;::IsEmpty()
{
    // If tail is NULL then the list is empty.
    return tail == NULL;
}
 
template &lt;class T&gt;
void CLinkedList&lt;T&gt;::AppendToTail(T value)
{
    // If list is empty then create new node, point tail to it and point tail to itself
    if (tail == NULL)
    {
        tail = new CLinkedListNode&lt;T&gt;(value);
        tail-&gt;next = tail;
    }
 
    // Otherwise append new node to tail and
    else
    {
        // Create temporaty pointer to tail.
        CLinkedListNode&lt;T&gt; *tmp = tail;
 
        // Create new tail node and point it to old tail's next node
        tail = new CLinkedListNode&lt;T&gt;(value, tail-&gt;next);
 
        // Point old tail to new tail.
        tmp-&gt;next = tail;
 
    }
}
 
template &lt;class T&gt;
T CLinkedList&lt;T&gt;::GetCurrentNode()
{
    // List is empty.
    if (IsEmpty())
    {
        return NULL;
    }
 
    // Current pointer has not been set.
    if (current == NULL)
    {
        // Point to head node.
        current = tail-&gt;next;
    }
 
    // Get data from current node.
    T data = current-&gt;data;
 
    // Set current node to the next node.
    current = current-&gt;next;
 
    // Return data.
    return data;
}
 
template &lt;class T&gt;
void CLinkedList&lt;T&gt;::Print()
{
    if (IsEmpty())
    {
        return;
    }
 
    CLinkedListNode&lt;T&gt; *tmp = tail-&gt;next;
    while (tmp != tail)
    {
        cout &lt;&lt; tmp-&gt;data &lt;&lt; &quot; &quot;;
        tmp = tmp-&gt;next;
    }
 
    cout &lt;&lt; tail-&gt;data &lt;&lt; &quot; &quot;;
}
