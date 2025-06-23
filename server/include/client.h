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

typedef struct client_s {
    int id;
    int fd;
    uint8_t level;
    bool is_elevating;
    int inventory[RESOURCE_TYPES];
    struct client_s *next;
    circular_buffer_t *buffer;
    char *message;
    vector2_t *position;
    direction_t direction;
} client_t;

#endif /* !CLIENT_H_ */
