/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

// TODO: only for gui connections
void command_sst(server_t *server, client_t *client, char *message)
{
    uint32_t freq = PARAMETERS->freq;

    sscanf(message, "sst %u\n", &freq);
    for (size_t i = 0; i < server->cons - 1; ++i) {
        send_message(client->fd, "sst %u\n", freq);
    }
}
