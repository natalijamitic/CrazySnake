#include "queue.h"
#include "gameplay.h"
#include <stdio.h>
#include <stdlib.h>

void header_copy(Header **new_snake, Header *snake)
{
	Pointer temp, new_list = NULL, new_element = NULL, last = NULL;
	*new_snake = (Header *)malloc(sizeof(Header));
	if (!(*new_snake)) exit(1);
	temp = snake->tail;

	while (temp)
	{
		new_element = (Element*)malloc(sizeof(Element));
		if (new_element)
		{
			new_element->column = temp->column;
			new_element->row = temp->row;
			new_element->next = NULL;
			if (last) last->next = new_element;
			last = new_element;

			if (new_list == NULL)
			{
				new_list = new_element;
				(*new_snake)->tail = new_element;
			}
			if (!temp->next) (*new_snake)->head = new_element;
			temp = temp->next;
		}
		else exit(1);
	}
}

void enqueue(Queue_header *qh, Header *header)
{
	if (qh->length<CAPACITY)
	{
		header_copy(&qh->queue[qh->rear], header);
		(qh->length)++;
		qh->rear = (qh->rear + 1) % CAPACITY;

	}
	else printf("Overflow!\n");
}

void dequeue(Queue_header *qh, Header **new_snake)
{
	if (qh->length>0)
	{
		*new_snake = (Header*)malloc(sizeof(Header));
		*new_snake = qh->queue[qh->front];
		(qh->length)--;
		qh->front = (qh->front + 1) % CAPACITY;
	}
	else exit(1);
}