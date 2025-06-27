/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/right.c
*/

#include "../../include/commands.h"

void command_right(server_t *server, client_t *client, char *message)
{
    (void)server;
    (void)message;
    client->direction = client->direction + 1 % 4;
    command_ok(client->fd);
}
