/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/
#ifndef STACK_HEADER
#define STACK_HEADER

#include "node.h"


typedef struct {
	int n;
	int nCount;
	sNode *pTop;
} stack;

//Returns a stack with size n.
stack* createStack(int n) {
	// Your code here
}

//Returns 1 if stack s is EMPTY, and 0 otherwise. The stack is empty if the value of the top pointer, pTop is NULL.
int stackEmpty(stack *s) {
	// Your code here
}

//Returns 1 if stack s is FULL, and 0 otherwise. The stack is full if the number of values inside the stack is equal to n.
int stackFull(stack *s) {
	// Your code here
}

//Adds the new value data at the top of the stack. This moves the top pointer, pTop, to point at the newly added data. This also increments nCount by 1.
void push(stack **s, char *data) {
	// Your code here
}

//Returns and removes the value pointed by the top pointer of the stack, pTop. This moves the top pointer, pTop, to point to the next newest value in the stack. This also decrements nCount by 1.
char* pop(stack **s) {
	// Your code here
}

//Displays the contents of the stack s following the last-in first-out (LIFO) policy.
void displayStack(stack *s) {
	// Your code here
}

//Returns, but does NOT remove, the value currently pointed by the top pointer, pTop.
char* top(stack *s) {
	// Your code here
}

#endif