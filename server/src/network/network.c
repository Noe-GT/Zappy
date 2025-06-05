/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** network
*/

#include "network.h"

network_t *init_network(size_t max_clients)
{
    network_t *net = malloc(sizeof(network_t));
    struct sockaddr_in *addr = make_addr(4000);

    net->main_socket = malloc(sizeof(socket_t));
    net->main_socket->addr = addr;
    net->main_socket->fd = create_socket(addr, sizeof(*addr), 200);
    if (net->main_socket->fd == -1)
        return NULL;
    net->sockets = malloc(sizeof(struct pollfd));
    net->sockets_n = 1;
    net->sockets[0].fd = net->main_socket->fd;
    net->sockets[0].events = POLLIN;
    net->client_list = init_client_list();
    return net;
}

void free_network(network_t *net)
{
    if (net == NULL)
        return;
    if (net->main_socket != NULL) {
        close(net->main_socket->fd);
        free(net->main_socket->addr);
        free(net->main_socket);
        free(net->sockets);
    }
    free(net);
}

static int check_event(network_t *net, int i)
{
    if (net->sockets[i].revents == POLLERR ||
        net->sockets[i].revents == POLLHUP ||
        net->sockets[i].revents == POLLNVAL) {
        printf("Error: client %d - bad revents (%d)\n", i,
            net->sockets[i].revents);
        client_remove(net, i);
        return -1;
    }
    if (net->sockets[i].revents == POLLIN) {
        if (net->sockets[i].fd == net->main_socket->fd) {
            client_new(net, net->main_socket->fd);
        } else
            client_handle(net, i);
    }
    return 0;
}

static int parse_clients(network_t *net)
{
    for (int i = 0; i < net->sockets_n; i++) {
        check_event(net, i);
    }
    return 0;
}

int network_handle(network_t *net)
{
    if (poll(net->sockets, net->sockets_n, -1) < 0) {
        perror("ERROR: poll failed");
        return -1;
    }
    return parse_clients(net);
}
