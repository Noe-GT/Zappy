/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/eject.c
*/

#include "../../include/commands.h"

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
    if (TILE.player_count == 1)
        return command_ko(client->fd);
    for (size_t i = 0; i < TILE.player_count; ++i) {
        eject(server, client, i);
    }
    for (size_t j = 0; j < TILE.player_count; ++j) {
        if (TILE.players[j]->id == client->id)
            continue;
        else
            send_message(TILE.players[j]->fd, "eject: %d\n",
                client->direction + 1);
    }
    for (size_t i = 0; i < server->cons; ++i) {
        if (server->clients[i]->is_gui)
            command_pex(server->clients[i]);
    }
    command_ok(client->fd);
}
