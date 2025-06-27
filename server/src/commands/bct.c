/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

void bct(server_t *server, client_t *client, uint32_t x, uint32_t y)
{
    send_message(client->fd, "bct %u %u %d %d %d %d %d %d %d\n", x, y,
        MAP->tiles[y][x].resources[FOOD],
        MAP->tiles[y][x].resources[LINEMATE],
        MAP->tiles[y][x].resources[DERAUMERE],
        MAP->tiles[y][x].resources[SIBUR],
        MAP->tiles[y][x].resources[MENDIANE],
        MAP->tiles[y][x].resources[PHIRAS],
        MAP->tiles[y][x].resources[THYSTAME]);
}

void command_bct(server_t *server, client_t *client, char *message)
{
    uint32_t x = 0;
    uint32_t y = 0;

    (void)server;
    (void)message;
    if (sscanf(message, "bct %u %u\n", &x, &y) == 2)
        bct(server, client, x, y);
    else
        command_sbp(client);
}
