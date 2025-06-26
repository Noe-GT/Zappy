/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/enw.c
*/

#include "../../include/commands.h"

void command_enw(server_t *server, client_t *client, egg_t *egg)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(client->fd, "enw #%u #%d %u %u", egg->id, client->id,
            egg->position->x, egg->position->y);
    }
}
