/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** queue
*/

#include "../../include/queue.h"

int_queue_t *queue_init(size_t size)
{
    int_queue_t *queue = malloc(sizeof(int_queue_t));

    queue->items = malloc(sizeof(int) * size);
    queue->front = -1;
    queue->back = 0;
    return queue;
}

void queue_push(int_queue_t *queue, int value)
{
    if (queue_full(queue)) {
        fprintf(stderr, "push: queue is full\n");
        return;
    }
    queue->items[queue->back] = value;
    queue->back++;
}

int queue_pop(int_queue_t *queue)
{
    if (queue_empty(queue)) {
        fprintf(stderr, "pop: queue is empty\n");
        return -1;
    }
    queue->front++;
    return queue->items[queue->front];
}

int queue_peek(int_queue_t *queue)
{
    if (queue_empty(queue)) {
        fprintf(stderr, "peek: queue is empty\n");
        return -1;
    }
    return queue->items[queue->front + 1];
}

bool queue_empty(int_queue_t *queue)
{
    if (queue->front + 1 == queue->back)
        return true;
    return false;
}

bool queue_full(int_queue_t *queue)
{
    if (queue->front == queue->back + 1)
        return true;
    return false;
}
