/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pie.c
*/

#include "../../include/commands.h"

void command_pie(server_t *server, client_t *client, bool success)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(client->fd, "pie %u %u %d\n", client->position->x,
            client->position->y, success);
    }
}
