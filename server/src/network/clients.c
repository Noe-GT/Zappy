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

    clients->n = 0;
    clients->available_ids = queue_init(MAX_CLIENTS);
    for (int i = 0; i < MAX_CLIENTS; i++)
        queue_push(clients->available_ids, i);
    return clients;
}

void client_manage(clients_t *clients, int i)
{
    (void)clients;
    (void)i;
}

void client_remove(clients_t *clients, int i)
{
    close(clients->fds[i].fd);
    queue_push(clients->available_ids, i);
}

struct pollfd set_pollfd(int new_fd)
{
    struct pollfd pfd;

    pfd.fd = new_fd;
    pfd.events = POLLIN;
    return pfd;
}

void client_new(clients_t *clients, int main_socket)
{
    struct sockaddr_in *addr;
    socklen_t addr_len;
    int new_fd;

    if (clients->n == MAX_CLIENTS) {
        perror("Max amount of clients reached");
        return;
    }
    addr = make_addr(main_socket);
    addr_len = sizeof(addr);
    new_fd = accept(main_socket, (struct sockaddr*)addr, &addr_len);
    if (new_fd < 0) {
        perror("ERROR: accept failed");
        free(addr);
        return;
    }
    clients->n++;
    clients->fds[queue_pop(clients->available_ids)] = set_pollfd(new_fd);
}
