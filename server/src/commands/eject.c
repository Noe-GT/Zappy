/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/eject.c
*/

#include "../../include/commands.h"

static void eject(server_t *server, client_t *client, client_t *to_eject)
{
    vector2_t old = {.x = to_eject->position->x, .y = to_eject->position->y};

    if (client->id == to_eject->id)
        return;
    if (strcmp(client->team, to_eject->team) == 0)
        return;
    move_player(server, to_eject, client->direction);
    remove_player_tile(server, to_eject, &old);
    add_player_tile(server, to_eject, to_eject->position);
}

void command_eject(server_t *server, client_t *client, char *message)
{
    (void)message;
    if (TILE.player_count == 1)
        return command_ko(client->fd);
    for (size_t i = 0; i < TILE.player_count; ++i)
        eject(server, client, TILE.players[i]);
    eject_eggs(&server->egg, server, client->position);
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
