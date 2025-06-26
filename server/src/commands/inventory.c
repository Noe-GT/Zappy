/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/inventory.c
*/

#include "../../include/commands.h"

void command_inventory(server_t *server, client_t *client, char *message)
{
    (void)server;
    (void)message;
    send_message(client->fd, "[food %d, linemate %d, deraumere %d, sibur %d, "
        "mendiane %d, phiras %d, thystame %d]\n",
        client->inventory[FOOD],
        client->inventory[LINEMATE], client->inventory[DERAUMERE],
        client->inventory[SIBUR], client->inventory[MENDIANE],
        client->inventory[PHIRAS], client->inventory[THYSTAME]);
}
