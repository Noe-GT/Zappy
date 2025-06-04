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
    pr_receive(net->sockets[i].fd, client->read_buffer);
    printf("(client) id: %d | read_buffer: %s\n",
        client->id, client->read_buffer->buffer);
}

void client_remove(network_t *net, int i)
{
    cl_remove(net->client_list, net->sockets[i].fd);
    close(net->sockets[i].fd);
    pollfd_array_remove(net->sockets, i, net->sockets_n + 1);
    net->sockets_n--;
}

void client_new(network_t *net, int main_socket_fd)
{
    struct sockaddr_in *addr;
    socklen_t addr_len;
    int new_fd;

    if (net->sockets_n - 1 == MAX_CLIENTS) {
        perror("Max amount of clients reached");
        return;
    }
    addr = make_addr(main_socket_fd);
    addr_len = sizeof(addr);
    new_fd = accept(main_socket_fd, (struct sockaddr*)addr, &addr_len);
    if (new_fd < 0) {
        perror("Accept failed");
        free(addr);
        return;
    }
    printf("new client (fd : %d)\n", new_fd);
    cl_add_end(net->client_list, new_fd);
    net->sockets = pollfd_array_add(net->sockets, new_fd, net->sockets_n + 1);
    net->sockets_n++;
}
