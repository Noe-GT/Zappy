/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

void server_ppo(server_t *server, client_t *client)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(server->clients[i]->fd, "ppo #%d %u %u %d\n", client->id,
            client->position->x, client->position->y, client->direction + 1);
    }
}

void command_ppo(server_t *server, client_t *client, char *message)
{
    int id = 0;

    if (sscanf(message, "ppo #%d\n", &id) != 1)
        return command_sbp(client);
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_ai)
            continue;
        if (server->clients[i]->id == id) {
            return (void)send_message(client->fd, "ppo #%d %u %u %d\n", id,
                server->clients[i]->position->x,
                server->clients[i]->position->y,
                server->clients[i]->direction + 1);
        }
    }
    return command_sbp(client);
}
