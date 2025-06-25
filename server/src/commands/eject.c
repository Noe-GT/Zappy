/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/eject.c
*/

#include "../../include/commands.h"

// TODO: Do we send expulsion to the client? We also send to the ais
static void eject(server_t *server, client_t *client, size_t i)
{
    vector2_t old = {.x = client->position->x, .y = client->position->y};

    if (server->map->tiles[client->position->y][client->position->x]
        .players[i]->id == client->id)
        return;
    forward(server, client);
    remove_player_tile(server, client, &old);
    add_player_tile(server, client, client->position);
}

void command_eject(server_t *server, client_t *client, char *message)
{
    (void)message;
    if (server->map->tiles[client->position->y][client->position->x]
        .player_count == 1)
        return command_ko(client->fd);
    for (size_t i = 0; i < server->map->tiles[client->position->y]
        [client->position->x].player_count; ++i) {
        eject(server, client, i);
    }
    command_ok(client->fd);
}
