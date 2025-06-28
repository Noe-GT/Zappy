/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/plv.c
*/

#include "../../include/commands.h"

void server_plv(server_t *server, client_t *client)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(server->clients[i]->fd, "plv #%d %d\n",
            client->id, client->level);
    }
}

void command_plv(server_t *server, client_t *client, char *message)
{
    int id = 0;

    if (sscanf(message, "plv #%d\n", &id) != 1)
        return command_sbp(client);
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_ai)
            continue;
        if (server->clients[i]->id == id) {
            return (void)send_message(client->fd, "plv #%d %d\n",
                id, server->clients[i]->level);
        }
    }
    return command_sbp(client);
}
