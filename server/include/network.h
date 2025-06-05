/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** network
*/

#ifndef NETWORK_H_
    #define NETWORK_H_
    #include "external.h"
    #include "client_list.h"
    #include "pollfd.h"
    #define MAX_CLIENTS 255

typedef struct clients_s {
    size_t max_clients;
} clients_t;

typedef struct socket_s {
    int fd;
    struct sockaddr_in *addr;
} socket_t;

typedef struct network_s {
    client_list_t *client_list;
    struct pollfd *sockets;
    size_t sockets_n;
    socket_t *main_socket;
    bool debug;
} network_t;

network_t *init_network(void);
void free_network(network_t *net);
int network_handle(network_t *net);

clients_t *init_clients(size_t max_clients);
void client_handle(network_t *net, int i);
void client_remove(network_t *net, int i);
void client_new(network_t *net, int main_socket_fd);
void client_send(int fd, const char *message);
void broadcast_message(network_t *net, const char *message);

struct sockaddr_in *make_addr(int port);
int create_socket(struct sockaddr_in *addr, socklen_t addrlen, int listen_n);

#endif /* !NETWORK_H_ */
