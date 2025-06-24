/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pin.c
*/

#include "../../include/commands.h"

void command_pin(server_t *server, client_t *client, char *message)
{
    (void)server;
    (void)message;
    send_message(client->fd, "pin #%d %u %u %d %d %d %d %d %d %d\n",
        client->id,
        client->position->x, client->position->y, client->inventory[FOOD],
        client->inventory[LINEMATE], client->inventory[DERAUMERE],
        client->inventory[SIBUR], client->inventory[MENDIANE],
        client->inventory[PHIRAS], client->inventory[THYSTAME]);
}
