#ifndef QUEUE_H
#define QUEUE_H

enum FLAG
{
	OVERRUN = 0x0001,
};

typedef struct
{
	int flags;
	int front;
	int rear;
	int size;
	int capacity;
	unsigned char *buffer;
} Queue;

void initialize_queue(int capacity, unsigned char *buffer, Queue *queue);
int enqueue(unsigned char data, Queue *queue);
int dequeue(Queue *queue);
int queue_size(Queue *queue);

#endif
