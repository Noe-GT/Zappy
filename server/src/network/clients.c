/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** clients
*/

#include "../../include/network.h"

void client_handle(network_t *net, int i)
{
    client_t *client = cl_get(net->client_list, net->sockets[i].fd);

    if (client == NULL)
        return;
    receive(net->sockets[i].fd, client->buffer);
    printf("(client) id: %d\n", client->id);
}

void client_remove(network_t *net, int i)
{
    cl_remove(net->client_list, net->sockets[i].fd);
    close(net->sockets[i].fd);
    pollfd_array_remove(net->sockets, i, net->sockets_n);
    net->sockets_n--;
}

void client_new(network_t *net, int main_socket_fd)
{
    struct sockaddr_in *addr;
    socklen_t addr_len = sizeof(struct sockaddr_in *);
    int new_fd;

    if (net->sockets_n - 1 == MAX_CLIENTS) {
        perror("Max amount of clients reached");
        return;
    }
    addr = make_addr(main_socket_fd);
    new_fd = accept(main_socket_fd, (struct sockaddr *)addr, &addr_len);
    if (new_fd < 0) {
        perror("Accept failed");
        free(addr);
        return;
    }
    printf("new client (fd : %d)\n", new_fd);
    cl_add_end(net->client_list, new_fd);
    net->sockets = pollfd_array_add(net->sockets, new_fd, net->sockets_n);
    net->sockets_n++;
}

void broadcast_message(network_t *net, const char *message)
{
    for (size_t i = 1; i < net->sockets_n; i++) {
        client_send(net->sockets[i].fd, message);
    }
}

void client_send(int fd, const char *message)
{
    size_t len = strlen(message);
    ssize_t sent = send(fd, message, len, 0);

    if (sent < 0) {
        perror("Send failed");
        return;
    }
}
