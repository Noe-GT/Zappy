/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/queue.c
*/

#include "../include/client.h"

queue_t *init_queue(char *command)
{
    queue_t *node = (queue_t *)malloc(sizeof(queue_t));

    if (node == NULL)
        return NULL;
    node->command = command;
    node->pending = false;
    return node;
}

queue_t *add_queue(queue_t *queue, char *command)
{
    queue_t *node = init_queue(command);

    if (node == NULL)
        return queue;
    node->next = queue;
    return node;
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
