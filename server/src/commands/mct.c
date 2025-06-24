/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

void command_mct(server_t *server, client_t *client, char *message)
{
    (void)message;
    for (uint32_t i = 0; i < server->parameters->height; ++i) {
        for (uint32_t j = 0; j < server->parameters->width; ++j) {
            bct(server, client, j, i);
        }
    }
}
