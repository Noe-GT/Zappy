/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pdi.c
*/

#include "../../include/commands.h"

void command_pdi(server_t *server, client_t *client)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (server->clients[i]->is_gui) {
            send_message(client->fd, "pdi #%d\n", client->id);
        }
    }
}
