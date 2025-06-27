/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/broadcast.c
*/

#include "../../include/commands.h"

void command_broadcast(server_t *server, client_t *client, char *message)
{
    char *text = message + strlen("broadcast ");

    for (uint64_t i = 0; i < server->cons - 1; ++i) {
        if (server->clients[i]->id == client->id) {
            command_ok(client->fd);
            continue;
        }
        if (server->clients[i]->is_ai)
            send_message(server->clients[i]->fd, message);
        if (server->clients[i]->is_gui)
            command_pbc(server->clients[i], "pbc #%d %s\n", client->id, text);
    }
}
