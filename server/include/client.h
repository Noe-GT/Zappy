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
    #include "../../protocol/include/protocol.h"

typedef struct client_s {
    int id;
    int fd;
    struct client_s *next;
    circular_buffer_t *buffer;
    char *message;
} client_t;

#endif /* !CLIENT_H_ */
