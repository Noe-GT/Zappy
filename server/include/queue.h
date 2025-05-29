/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** queue
*/

#ifndef QUEUE_H_
    #define QUEUE_H_
    #include <stdio.h>
    #include <stdbool.h>

typedef struct int_queue_s {
    int *items;
    int front;
    int back;
} int_queue_t;

int_queue_t *queue_init(size_t size);
void queue_push(int_queue_t *queue, int value);
int queue_pop(int_queue_t *queue);
int queue_peek(int_queue_t *queue);
bool queue_empty(int_queue_t *queue);
bool queue_full(int_queue_t *queue);

#endif /* !QUEUE_H_ */
