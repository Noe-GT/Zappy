/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#include "../include/server.h"
#include "../include/commands.h"

server_t *init_server()
{
    server_t *server = malloc(sizeof(server_t));

    server->network = init_network();
    if (server->network == NULL) {
        free(server);
        return NULL;
    }
    return server;
}

void free_server(server_t *server)
{
    if (server == NULL)
        return;
    free_network(server->network);
    free(server);
}

void server_run(server_t *server)
{
    while (true) {
        network_handle(server->network);
        handle_client_commands(server->network);
    }
    free_server(server);
}
