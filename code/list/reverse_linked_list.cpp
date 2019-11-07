#include<stdio.h>

struct Node
{
	Object data;
	struct Node *next;
};

struct Node* head;

//// iterative method
time complexity: O(n)
space complexity: O(1)
void Reverse() 
{
	struct Node *current, *prev, *next;
	current = head;
	prev = NULL;
	
	while(current != NULL)
	{
		next = current->next;  // store the next node
		current->next = prev;  // current point to prev
		
		prev = current;
		current = next;
	}
	head = prev;
}

//// print elements of a linked list in forward and reverse order using recursion
void Print(struct Node *p) 
{
	// print in forward order
	if(p==NULL) return; // Exit Condition
	printf("%d ", p->data);
	Print(p->next);
}
// for normal print, recursive approach is worst than iterative method.
// iterative: only use one temporary var
// recursive: many section of stack due to functions call

void RversePrint(struct Node *p) 
{
	// print in reverse order
	if(p==NULL) return;
	RversePrint(p->next);
	printf("%d ", p->data);
}

//// recursion method
time complexity: O(n)
space complexity: O(n)  implicit stack
struct Node* head;
void Rverse(struct Node *p) 
{
	if(p==NULL)  // exit condition
	{
		head = p;
		return;
	}
	Rverse(p->next);
	struct Node* q = p->next;
	q->next = p;
	p->next = NULL;
}

head node is the frist node of the list,
head is the pointer

// explicit stack to reverse
void Reverse(){
	stack<Node *> S;

	Node *tmp = head;
	while(tmp != nullptr){
		S.push(tmp);
		tmp = tmp->next;
	}
	
	tmp = S.top(); head = tmp;
	S.pop();
	while(!S.empty()){
		tmp->next = S.top();
		S.pop();
		tmp = tmp->next;
	}
	tmp->next = nullptr;
}