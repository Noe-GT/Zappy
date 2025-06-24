/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/game.c
*/

#include "../include/server.h"

void game_logic(server_t *server)
{
    if (!server || !server->clients)
        return;
    handle_ressource(server);
    for (size_t i = 0; server->clients[i] != NULL; ++i) {
        handle_vision(server, server->clients[i]);
    }
}
