/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/connections.c
*/

#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <poll.h>
#include <stdlib.h>

#include "../include/server.h"

void destroy_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; ++i)
        free(tab[i]);
    free(tab);
}

void remove_client(server_t *server, size_t index)
{
    client_t *client = server->clients[index - 1];

    close(server->clfds[index].fd);
    for (size_t i = index; i < server->cons - 1; i++) {
        server->clfds[i] = server->clfds[i + 1];
        server->clients[i - 1] = server->clients[i];
    }
    --server->cons;
    if (server->cons > 0) {
        server->clfds = realloc(server->clfds,
            sizeof(struct pollfd) * server->cons);
        server->clients = realloc(server->clients,
            sizeof(client_t *) * server->cons);
    }
    free(client);
}

static void new_connection(server_t *server, int confd)
{
    client_t *client;

    server->clfds = realloc(server->clfds,
        sizeof(struct pollfd) * (server->cons + 1));
    server->clfds[server->cons].fd = confd;
    server->clfds[server->cons].events = POLLIN;
    server->clfds[server->cons].revents = 0;
    server->clients = realloc(server->clients,
        sizeof(client_t *) * (server->cons + 1));
    server->clients[server->cons - 1] = (client_t *)malloc(sizeof(client_t));
    server->clients[server->cons] = NULL;
    client = server->clients[server->cons - 1];
    client->buffer = create_buffer();
    client->message = NULL;
    ++server->cons;
}

void attach_clients(server_t *server)
{
    struct sockaddr_in cli;
    socklen_t len = sizeof(cli);
    int confd;

    confd = accept(server->sockfd, (struct sockaddr *)&cli, &len);
    if (errno == EAGAIN || errno == EWOULDBLOCK)
        return;
    if (confd <= 0)
        return (void)perror("Accept failed");
    new_connection(server, confd);
    printf("New client connected. Total clients: %lu\n", server->cons - 1);
}
