/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/left.c
*/

#include "../../include/commands.h"

void command_left(server_t *server, client_t *client, char *message)
{
    (void)server;
    (void)message;
    if (client->direction == UP) {
        client->direction = LEFT;
        return;
    } else {
        client->direction -= 1;
    }
    command_ok(client->fd);
}
