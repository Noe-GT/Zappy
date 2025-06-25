/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/eject.c
*/

#include "../../include/commands.h"

// TODO:
void command_eject(server_t *server, client_t *client, char *message)
{
    if (server->map->tiles[client->position->y][client->position->x]
        .player_count == 1)
        return command_ko(client->fd);
    for (size_t i = 0; i < server->map->tiles[client->position->y]
        [client->position->x].player_count; ++i) {
        if (server->map->tiles[client->position->y][client->position->x]
            .players[i]->id == client->id)
            continue;
    }
}
