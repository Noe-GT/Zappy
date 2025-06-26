/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

void command_tna(server_t *server, client_t *client, char *message)
{
    (void)message;
    for (uint16_t i = 0; i < server->parameters->team_count; ++i) {
        send_message(client->fd, "tna %s\n", PARAMETERS->team_names[i]);
    }
}
