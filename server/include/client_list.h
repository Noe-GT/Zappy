/*
** EPITECH PROJECT, 2025
** zappy -server*
** File description:
** *
*/

#ifndef CLIENT_LIST_H_
    #define CLIENT_LIST_H_

    #include <stdio.h>
    #include <stdlib.h>

    #include "../../protocol/include/protocol.h"

typedef struct client_s {
    int id;
    circular_buffer_t *read_buffer;
    struct client_s *next;
} client_t;

typedef struct client_list_s {
    client_t *begin;
    client_t *end;
} client_list_t;

client_list_t *init_client_list(void);
client_list_t *cl_destroy(client_list_t *list);
void cl_add_end(client_list_t *list, int id);
void cl_remove(client_list_t *list, int id);
client_t *cl_get(client_list_t *list, int id);
void cl_display(client_list_t *list);

#endif /* !CLIENT_LIST_H_ */
