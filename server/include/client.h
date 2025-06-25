/*
** EPITECH PROJECT, 2025
** zappy -server*
** File description:
** *
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>

    #include "../../protocol/include/protocol.h"
    #include "game.h"
    #include "vector.h"

typedef struct queue_s {
    char *command;
    bool pending;
    struct queue_s *next;
} queue_t;

typedef struct client_s {
    int id;
    int fd;
    uint8_t level;
    bool is_elevating;
    int inventory[RESOURCE_TYPES];
    struct client_s *next;
    circular_buffer_t *buffer;
    vector2_t *position;
    direction_t direction;
    uint64_t cooldown;
    queue_t *queue;
    char *team;
    bool is_gui;
    bool is_ai;
} client_t;

queue_t *init_queue(char *command);
queue_t *add_queue(queue_t *queue, char *command);
void destroy_queue(queue_t *queue);
queue_t *shift_queue(queue_t *queue);

#endif /* !CLIENT_H_ */
