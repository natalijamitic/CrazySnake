#include "queue.h"
#include "gameplay.h"
#include <stdio.h>
#include <stdlib.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

static void delete_snake(Header **header)
{
	Element *tail = (*header)->tail;
	Element *temp;
	while (tail)
	{
		temp = tail;
		tail = tail->next;
		free(temp);
	}
	free(*header);
}

static void move_snake(int m, int n, Move move, Header * header)
{
	int x = header->head->row, y = header->head->column;
	switch (move) {
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	case UP:
		x--;
		break;
	}

	if (x == -1) x = m - 1;
	if (x == m) x = 0;
	if (y == -1) y = n - 1;
	if (y == n) y = 0;

	Pointer temp;
	temp = (Pointer)malloc(sizeof(Element));
	temp->column = y;
	temp->row = x;
	header->head->next = temp;
	temp->next = NULL;
	header->head = temp;
	temp = header->tail;
	header->tail = header->tail->next;
	free(temp);
}

static _Bool inSnake(Header *header, int row, int column)
{
	Pointer temp = header->tail;
	while (temp)
	{
		if (temp->row == row && temp->column == column) return 1;
		temp = temp->next;
	}
	return 0;
}

int shortest_path_length(short **board, Header header, Fruit fruit, int m, int n)
{
	Queue_header *queue_header = (Queue_header *)calloc(1, sizeof(Queue_header));
	if (!queue_header) return NULL;
	queue_header->queue = (Header*)calloc(CAPACITY, sizeof(Header));
	if (!queue_header->queue) return NULL;
	Header *temp = 0, *temp1, *temp2, *temp3, *temp4;
	short **trace;
	_Bool  **visit;

	visit = (_Bool**)malloc(m * sizeof(_Bool*));
	if (visit)
		for (int i = 0; i < m; i++)
		{
			visit[i] = (_Bool*)calloc(n, sizeof(_Bool));
			if (!visit[i]) return NULL;
		}
	else
		return NULL;
	trace = (short**)malloc(m * sizeof(short*));
	if (trace)
		for (int i = 0; i < m; i++)
		{
			trace[i] = (short*)calloc(n, sizeof(short));
			if (!trace[i]) return NULL;
		}
	else
		return NULL;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			trace[i][j] = 1000;
			if (board[i][j] == 2)
				visit[i][j] = 1;

		}
	visit[header.head->row][header.head->column] = 1;
	trace[header.head->row][header.head->column] = 0;

	enqueue(queue_header, &header);

	while (queue_header->length > 0)
	{
		dequeue(queue_header, &temp);

		if (temp->head->row == fruit.fruit_row && temp->head->column == fruit.fruit_column) break;

		header_copy(&temp1, temp);
		header_copy(&temp2, temp);
		header_copy(&temp3, temp);
		header_copy(&temp4, temp);
		move_snake(m, n, DOWN, temp1);
		move_snake(m, n, UP, temp2);
		move_snake(m, n, LEFT, temp3);
		move_snake(m, n, RIGHT, temp4);

		if (!visit[temp1->head->row][temp1->head->column] && !inSnake(temp, temp1->head->row, temp1->head->column))
		{
			enqueue(queue_header, temp1);
			visit[temp1->head->row][temp1->head->column] = 1;
			trace[temp1->head->row][temp1->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		if (!visit[temp2->head->row][temp2->head->column] && !inSnake(temp, temp2->head->row, temp2->head->column))
		{
			enqueue(queue_header, temp2);
			visit[temp2->head->row][temp2->head->column] = 1;
			trace[temp2->head->row][temp2->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		if (!visit[temp3->head->row][temp3->head->column] && !inSnake(temp, temp3->head->row, temp3->head->column))
		{
			enqueue(queue_header, temp3);
			visit[temp3->head->row][temp3->head->column] = 1;
			trace[temp3->head->row][temp3->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		if (!visit[temp4->head->row][temp4->head->column] && !inSnake(temp, temp4->head->row, temp4->head->column))
		{
			enqueue(queue_header, temp4);
			visit[temp4->head->row][temp4->head->column] = 1;
			trace[temp4->head->row][temp4->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		delete_snake(&temp1);
		delete_snake(&temp2);
		delete_snake(&temp3);
		delete_snake(&temp4);
		delete_snake(&temp);

	}
	int row = fruit.fruit_row, column = fruit.fruit_column, rowmin = row, columnmin = column;
	int rez;
	rez = trace[row][column];

	for (int i = 0; i < m; i++)
	{
		free(visit[i]);
		free(trace[i]);
	}
	free(visit);
	free(trace);

	Element *temp_snake;
	for (int i = queue_header->front; i != queue_header->rear; i = (i + 1) % CAPACITY)
	{
		while (queue_header->queue[i]->tail)
		{
			temp_snake = queue_header->queue[i]->tail;
			queue_header->queue[i]->tail = queue_header->queue[i]->tail->next;
			free(temp_snake);
		}
		free(queue_header->queue[i]);
	}

	free(queue_header->queue);
	free(queue_header);

	return rez;
}


Move *shortest_path(short **board, Header header, Fruit fruit, int m, int n, int *len)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Queue_header *queue_header = (Queue_header *)calloc(1, sizeof(Queue_header));
	if (!queue_header) return NULL;
	queue_header->queue = (Header*)calloc(CAPACITY, sizeof(Header));
	if (!queue_header->queue) return NULL;
	Header *temp = 0, *temp1, *temp2, *temp3, *temp4;
	short **trace;
	_Bool  **visit;

	visit = (_Bool**)malloc(m * sizeof(_Bool*));
	if (visit)
		for (int i = 0; i < m; i++)
		{
			visit[i] = (_Bool*)calloc(n, sizeof(_Bool));
			if (!visit[i]) return NULL;
		}
	else
		return NULL;
	trace = (short**)malloc(m * sizeof(short*));
	if (trace)
		for (int i = 0; i < m; i++)
		{
			trace[i] = (short*)calloc(n, sizeof(short));
			if (!trace[i]) return NULL;
		}
	else
		return NULL;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			trace[i][j] = 1000;
			if (board[i][j] == 2)
				visit[i][j] = 1;

		}
	visit[header.head->row][header.head->column] = 1;
	trace[header.head->row][header.head->column] = 0;

	enqueue(queue_header, &header);

	while (queue_header->length > 0)
	{
		dequeue(queue_header, &temp);

		if (temp->head->row == fruit.fruit_row && temp->head->column == fruit.fruit_column) break;

		header_copy(&temp1, temp);
		header_copy(&temp2, temp);
		header_copy(&temp3, temp);
		header_copy(&temp4, temp);
		move_snake(m, n, DOWN, temp1);
		move_snake(m, n, UP, temp2);
		move_snake(m, n, LEFT, temp3);
		move_snake(m, n, RIGHT, temp4);

		if (!visit[temp1->head->row][temp1->head->column] && !inSnake(temp, temp1->head->row, temp1->head->column))
		{
			enqueue(queue_header, temp1);
			visit[temp1->head->row][temp1->head->column] = 1;
			trace[temp1->head->row][temp1->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		if (!visit[temp2->head->row][temp2->head->column] && !inSnake(temp, temp2->head->row, temp2->head->column))
		{
			enqueue(queue_header, temp2);
			visit[temp2->head->row][temp2->head->column] = 1;
			trace[temp2->head->row][temp2->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		if (!visit[temp3->head->row][temp3->head->column] && !inSnake(temp, temp3->head->row, temp3->head->column))
		{
			enqueue(queue_header, temp3);
			visit[temp3->head->row][temp3->head->column] = 1;
			trace[temp3->head->row][temp3->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		if (!visit[temp4->head->row][temp4->head->column] && !inSnake(temp, temp4->head->row, temp4->head->column))
		{
			enqueue(queue_header, temp4);
			visit[temp4->head->row][temp4->head->column] = 1;
			trace[temp4->head->row][temp4->head->column] = trace[temp->head->row][temp->head->column] + 1;
		}

		delete_snake(&temp1);
		delete_snake(&temp2);
		delete_snake(&temp3);
		delete_snake(&temp4);
		delete_snake(&temp);

	}

	int row = fruit.fruit_row, column = fruit.fruit_column, rowmin = row, columnmin = column;
	*len = trace[row][column];

	Move *moves = (Move*)malloc(*len * sizeof(Move));
	if (!moves) exit(1);
	short min;

	for (int i = *len - 1; i >= 0; i--)
	{
		if (*len == 1000)
		{
			moves = 0;
			break;
		}

		min = trace[row][column];

		if (min == 0) {
			min = 0;
		}

		if (min - 1 == trace[row - 1 >= 0 ? row - 1 : m - 1][column])
		{
			rowmin = row - 1 >= 0 ? row - 1 : m - 1;
			min = trace[rowmin][column];
			moves[i] = DOWN;
			columnmin = column;
		}

		if (min - 1 == trace[row + 1 < m ? row + 1 : 0][column])
		{
			rowmin = row + 1 < m ? row + 1 : 0;
			min = trace[rowmin][column];
			moves[i] = UP;
			columnmin = column;
		}

		if (min - 1 == trace[row][column - 1 >= 0 ? column - 1 : n - 1])
		{
			columnmin = column - 1 >= 0 ? column - 1 : n - 1;
			min = trace[row][columnmin];
			moves[i] = RIGHT;
			rowmin = row;
		}

		if (min - 1 == trace[row][column + 1 < n ? column + 1 : 0])
		{
			columnmin = column + 1 < n ? column + 1 : 0;
			min = trace[row][columnmin];
			moves[i] = LEFT;
			rowmin = row;
		}
		row = rowmin;
		column = columnmin;
	}

	for (int i = 0; i < m; i++)
	{
		free(visit[i]);
		free(trace[i]);
	}
	free(visit);
	free(trace);


	Element *temp_snake;
	for (int i = queue_header->front; i != queue_header->rear; i = (i + 1) % CAPACITY)
	{
		while (queue_header->queue[i]->tail)
		{
			temp_snake = queue_header->queue[i]->tail;
			queue_header->queue[i]->tail = queue_header->queue[i]->tail->next;
			free(temp_snake);
		}
		free(queue_header->queue[i]);
	}

	free(queue_header->queue);
	free(queue_header);

	return moves;
}
