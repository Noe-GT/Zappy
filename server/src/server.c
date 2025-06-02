/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#include "../include/server.h"

server_t *init_server(void)
{
    server_t *server = malloc(sizeof(server_t));

    server->network = init_network();
    if (server->network == NULL)
        return NULL;
    return server;
}

int server_run(server_t *server)
{
    while (1) {
        network_handle(server->network);
    }
    return 0;
}
