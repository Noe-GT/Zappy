/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** network
*/

#ifndef NETWORK_H_
    #define NETWORK_H_
    #include "external.h"
    #include "queue.h"

typedef struct clients_s {
    struct pollfd *fds;
    size_t n;
    int_queue_t *available_ids;
} clients_t;

typedef struct network_s {
    clients_t *clients;
    int main_socket;
} network_t;

network_t *init_network(void);
int handle_network(network_t *net);

#endif /* !NETWORK_H_ */
