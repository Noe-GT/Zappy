/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** clients
*/

#include "../../include/network.h"

clients_t *init_clients(void)
{
    clients_t *clients = malloc(sizeof(clients_t));

    clients->fds = malloc(sizeof(struct pollfd) * MAX_CLIENTS + 1);
    clients->clients = malloc(sizeof(client_t) * MAX_CLIENTS + 1);
    memset(clients->fds, 0, sizeof(*clients->fds));
    clients->n = 0;
    clients->available_ids = queue_init(MAX_CLIENTS);
    for (int id = 1; id <= MAX_CLIENTS; id++)
        queue_push(clients->available_ids, id);
    return clients;
}

void client_handle(clients_t *clients, int i)
{
    printf("(client) id: %d | fd : %d", i, clients->fds[i].fd);
}

void client_remove(clients_t *clients, int i)
{
    close(clients->fds[i].fd);
    queue_push(clients->available_ids, i);
}

static struct pollfd set_pollfd(int new_fd)
{
    struct pollfd pfd;

    pfd.fd = new_fd;
    pfd.events = POLLIN;
    return pfd;
}

void client_new(clients_t *clients, int main_socket_fd)
{
    struct sockaddr_in *addr;
    socklen_t addr_len;
    int new_fd;

    if (clients->n == MAX_CLIENTS) {
        perror("Max amount of clients reached");
        return;
    }
    addr = make_addr(main_socket_fd);
    addr_len = sizeof(addr);
    new_fd = accept(main_socket_fd, (struct sockaddr*)addr, &addr_len);
    if (new_fd < 0) {
        perror("ERROR: accept failed");
        free(addr);
        return;
    }
    clients->n++;
    printf("new client (id : %d | fd : %d)\n",
        queue_peek(clients->available_ids), new_fd);
    clients->fds[queue_pop(clients->available_ids)] = set_pollfd(new_fd);
}
