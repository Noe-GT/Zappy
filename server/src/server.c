/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#include "../include/server.h"

server_t *init_server()
{
    server_t *server = malloc(sizeof(server_t));

    server->network = init_network();
    return server;
}

int run_server(server_t *server)
{
    return 0;
}
