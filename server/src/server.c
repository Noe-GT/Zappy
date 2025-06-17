/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#include "../include/server.h"
#include "../include/commands.h"

void init_server(server_t *server)
{
    server->network = init_network();
    if (server->network == NULL) {
        free(server);
    }
}

void free_server(server_t *server)
{
    if (server == NULL)
        return;
    free_network(server->network);
    for (int i = 0; i < server->parameters->team_count; ++i)
        free(server->parameters->team_names[i]);
    free(server->parameters->team_names);
    free(server->parameters);
}

void server_run(server_t *server)
{
    while (true) {
        network_handle(server->network);
        handle_client_commands(server);
    }
    free_server(server);
}
