/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** network
*/

#include "../../include/network.h"

network_t *init_network(void)
{
    network_t *net = malloc(sizeof(network_t));
    struct sockaddr_in *addr = make_addr(4000);

    net->main_socket = malloc(sizeof(socket_t));
    net->main_socket->addr = addr;
    net->main_socket->fd = create_socket(addr, sizeof(*addr), 200);
    if (net->main_socket->fd == -1)
        return NULL;
    net->clients = init_clients();
    net->clients->fds[0].fd = net->main_socket->fd;
    net->clients->fds[0].events = POLLIN;
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
    }
    if (net->clients != NULL) {
        cl_destroy(net->clients->client_list);
        free(net->clients->fds);
        queue_destroy(net->clients->available_ids);
        free(net->clients);
    }
    free(net);
}

static int check_event(network_t *net, int i)
{
    if (net->clients->fds[i].revents == POLLERR ||
        net->clients->fds[i].revents == POLLHUP ||
        net->clients->fds[i].revents == POLLNVAL) {
        printf("Error: client %d - bad revents (%d)\n", i,
            net->clients->fds[i].revents);
        client_remove(net->clients, i);
        return -1;
    }
    if (net->clients->fds[i].revents == POLLIN) {
        if (net->clients->fds[i].fd == net->main_socket->fd) {
            client_new(net->clients, net->main_socket->fd);
        } else
            client_handle(net->clients, i);
    }
    return 0;
}

static int parse_clients(network_t *net)
{
    int sokets_n = net->clients->n + 1;

    for (int i = 0; i < sokets_n; i++) {
        check_event(net, i);
    }
    return 0;
}

int network_handle(network_t *net)
{
    printf("clients : %ld\n", net->clients->n);
    if (poll(net->clients->fds, net->clients->n + 1, -1) < 0) {
        perror("ERROR: poll failed");
        return -1;
    }
    return parse_clients(net);
}
