/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pdr.c
*/

#include "../../include/commands.h"

void command_pdr(server_t *server, client_t *client, int resid)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(server->clients[i]->fd, "pdr #%d %d\n",
            client->id, resid);
    }
}
