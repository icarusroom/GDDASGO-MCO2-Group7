/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/
#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include "node.h"

typedef struct {
	int n;
	int nCount;
	sNode *pHead;
	sNode *pTail;
} queue;

//Returns a queue with size n.
queue* createQueue(int n) {
	// Your code here
}

//Returns 1 if queue q is EMPTY, and 0 otherwise. The queue is empty if the value of both the head pointer, pHead, and the tail pointer, pHead, s NULL.
int queueEmpty(queue *q) {
	// Your code here
}

//Returns 1 if queue q is FULL, and 0 otherwise. The queue is full if the number of values inside the queue is equal to n-1.
int queueFull(queue *q) {
	// Your code here
}

//Adds the new value data at the tail of the queue. This moves the tail pointer, pTail, to point at the newly added data. This also increments nCount by 1.
void enqueue(queue **q, char *data) {
	// Your code here
}

//Returns and removes the value pointed by the head pointer of the queue, pHead. This moves the head pointer, pHead, to point to the next older value in the queue. This also decrements nCount by 1.
char* dequeue(queue **q) {
    // Your code here
}

//Displays the contents of the queue q following the first-in first-out (FIFO) policy.
void displayQueue(queue *q) {
	// Your code here
}

//Returns, but does NOT remove, the value currently pointed by the head pointer, pHead.
char* head(queue *q) {
	// Your code here
}

//Returns, but does NOT remove, the value currently pointed by the tail pointer, pTail.
char* tail(queue *q) {
	// Your code here
}

#endif