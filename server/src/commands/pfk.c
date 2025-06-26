/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pfk.c
*/

#include "../../include/commands.h"

void command_pfk(server_t *server, client_t *client)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(client->fd, "pfk #%d\n", client->id);
    }
}
