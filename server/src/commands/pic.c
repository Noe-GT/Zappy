/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pic.c
*/

#include "../../include/commands.h"

void command_pic(server_t *server, client_t *client)
{
    char buf[4096] = {0};

    sprintf(buf, "pic %u %u #%d", client->position->x,
        client->position->y, client->id);
    for (uint16_t i = 0; i < TILE.player_count; ++i) {
        if (TILE.players[i]->id == client->id)
            continue;
        sprintf(buf + strlen(buf), " #%d", TILE.players[i]->id);
    }
    strcat(buf, "\n");
    printf("%s", buf);
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (server->clients[i]->is_gui)
            send_message(server->clients[i]->fd, buf);
    }
}
