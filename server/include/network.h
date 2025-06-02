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
    #define MAX_CLIENTS 255

typedef struct client_s {
    int id;
    char *read_buffer;
} client_t;

typedef struct clients_s {
    struct pollfd *fds;
    client_t *clients;
    size_t n;
    int_queue_t *available_ids;
} clients_t;

typedef struct socket_s {
    int fd;
    struct sockaddr_in *addr;
} socket_t;

typedef struct network_s {
    clients_t *clients;
    socket_t *main_socket;
} network_t;

network_t *init_network(void);
int network_handle(network_t *net);

clients_t *init_clients(void);
void client_handle(clients_t *clients, int i);
void client_remove(clients_t *clients, int i);
void client_new(clients_t *clients, int main_socket_fd);

struct sockaddr_in *make_addr(int port);
int create_socket(struct sockaddr_in *addr, socklen_t addrlen, int listen_n);

#endif /* !NETWORK_H_ */
