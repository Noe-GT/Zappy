/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#include "../include/server.h"

server_t *init_server(int max_clients)
{
    server_t *server = malloc(sizeof(server_t));

    server->network = init_network(max_clients);
    if (server->network == NULL)
        return NULL;
    return server;
}

void free_server(server_t *server)
{
    if (server == NULL)
        return;
    free_network(server->network);
    free(server);
}

int server_run(server_t *server)
{
    while (1) {
        network_handle(server->network);
    }
    free_server(server);
    return 0;
}
