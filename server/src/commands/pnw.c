/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pnw.c
*/

#include "../../include/commands.h"

void command_pnw(server_t *server, client_t *client)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(server->clients[i]->fd, "pnw #%d %u %u %d %u %s\n",
            client->id, client->position->x, client->position->y,
            client->direction + 1, client->level, client->team);
    }
}
