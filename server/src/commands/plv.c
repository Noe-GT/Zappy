/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/plv.c
*/

#include "../../include/commands.h"

void command_plv(server_t *server, client_t *client, char *message)
{
    (void)server;
    (void)message;
    send_message(client->fd, "plv #%d %d\n", client->id, client->level);
}
