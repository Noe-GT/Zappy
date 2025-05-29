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

    return net;
}

static int check_event(network_t *net, int i)
{
    if (net->clients->fds[i].revents == POLLERR ||
        net->clients->fds[i].revents == POLLHUP ||
        net->clients->fds[i].revents == POLLNVAL) {
        printf("Error: client %d - bad revents (%d)\n", i,
            net->clients->fds[i].revents);
        client_remove(net, i);
        return -1;
    }
    if (net->clients->fds[i].revents == POLLIN) {
        if (net->clients->fds[i].fd == net->main_socket)
            client_new(net, net->main_socket);
        else
            client_manage(net, i);
    }
    return 0;
}

static int parse_clients(network_t *net)
{
    int clientn = net->clients->n;

    for (int i = 0; i < clientn; i++) {
        check_event(net, i);
    }
    return 0;
}

int handle_network(network_t *net)
{
    if (poll(net->clients->fds, net->clients->n, -1) < 0) {
        perror("ERROR: poll failed");
        return -1;
    }
    return parse_clients(net);
}
