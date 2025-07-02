/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

void server_mct(server_t *server)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_gui)
            continue;
        command_mct(server, server->clients[i], NULL);
    }
}

void command_mct(server_t *server, client_t *client, char *message)
{
    (void)message;
    for (uint32_t i = 0; i < server->parameters->height; ++i) {
        for (uint32_t j = 0; j < server->parameters->width; ++j) {
            bct(server, client, j, i);
        }
    }
}
