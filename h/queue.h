#ifndef __queue_h
#define __queue_h
#include "setup.h"
#define CAPACITY 3000

typedef struct qheader {
	Header **queue;
	int front;
	int rear;
	int length;
} Queue_header;
//Add ellement to queue.
void enqueue(Queue_header *, Header*);
//Delete element from queue. 
void dequeue(Queue_header *, Header **);
// Copy snake header.
void header_copy(Header**, Header*);
#endif