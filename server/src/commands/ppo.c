/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

void command_ppo(server_t *server, client_t *client, char *message)
{
    (void)server;
    (void)message;
    send_message(client->fd, "ppo #%d %u %u %d\n", client->id,
        client->position->x, client->position->y, client->direction + 1);
}
