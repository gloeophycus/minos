#include "queue.h"

void initialize_queue(int capacity, unsigned char *buffer, Queue *queue)
{
	queue->flags = 0;
	queue->front = 0;
	queue->rear = 0;
	queue->size = 0;
	queue->capacity = capacity;
	queue->buffer = buffer;
}

int enqueue(unsigned char data, Queue *queue)
{
	if (queue->size == queue->capacity)
	{
		queue->flags |= OVERRUN;
		return -1;
	}

	queue->buffer[queue->rear++] = data;
	if (queue->rear == queue->capacity)
	{
		queue->rear = 0;
	}
	queue->size++;
	return 0;
}

int dequeue(Queue *queue)
{
	if (queue->size == 0)
	{
		return -1;
	}

	int data = queue->buffer[queue->front++];
	if (queue->front == queue->capacity)
	{
		queue->front = 0;
	}
	queue->size--;
	return data;
}

int queue_size(Queue *queue)
{
	return queue->size;
}