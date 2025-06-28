/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pin.c
*/

#include "../../include/commands.h"

void server_pin(server_t *server, client_t *client)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        send_message(server->clients[i]->fd, "pin #%d %u %u "
            "%d %d %d %d %d %d %d\n", client->id,
            client->position->x, client->position->y, client->inventory[FOOD],
            client->inventory[LINEMATE], client->inventory[DERAUMERE],
            client->inventory[SIBUR], client->inventory[MENDIANE],
            client->inventory[PHIRAS], client->inventory[THYSTAME]);
    }
}

void command_pin(server_t *server, client_t *client, char *message)
{
    int id = 0;

    if (sscanf(message, "pin #%d\n", &id) != 1)
        return command_sbp(client);
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_ai)
            continue;
        if (server->clients[i]->id == id) {
            return (void)send_message(client->fd, "pin #%d %u %u "
                "%d %d %d %d %d %d %d\n", id, server->clients[i]->position->x,
                server->clients[i]->position->y,
                server->clients[i]->inventory[FOOD],
                server->clients[i]->inventory[LINEMATE],
                server->clients[i]->inventory[DERAUMERE],
                server->clients[i]->inventory[SIBUR],
                server->clients[i]->inventory[MENDIANE],
                server->clients[i]->inventory[PHIRAS],
                server->clients[i]->inventory[THYSTAME]);
        }
    }
}
