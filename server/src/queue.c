/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/queue.c
*/

#include "../include/client.h"

static queue_t *init_queue(char *command)
{
    queue_t *node = (queue_t *)malloc(sizeof(queue_t));

    if (node == NULL)
        return NULL;
    node->command = command;
    node->pending = false;
    node->next = NULL;
    return node;
}

static queue_t *queue_last(queue_t *queue)
{
    if (queue == NULL)
        return NULL;
    if (queue->next == NULL)
        return queue;
    return queue_last(queue->next);
}

size_t queue_len(queue_t *queue)
{
    if (queue == NULL)
        return 0;
    return 1 + queue_len(queue->next);
}

queue_t *add_queue(queue_t *queue, char *command)
{
    queue_t *node = init_queue(command);
    queue_t *last = queue_last(queue);

    if (node == NULL)
        return queue;
    if (last == NULL)
        return node;
    last->next = node;
    return queue;
}

void destroy_queue(queue_t *queue)
{
    if (queue == NULL)
        return;
    destroy_queue(queue->next);
    free(queue->command);
}

queue_t *shift_queue(queue_t *queue)
{
    queue_t *first;

    if (queue == NULL)
        return queue;
    first = queue->next;
    free(queue->command);
    free(queue);
    return first;
}
