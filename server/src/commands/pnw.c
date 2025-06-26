/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pnw.c
*/

#include "../../include/commands.h"

void command_pnw(client_t *client)
{
    send_message(client->fd, "pnw #%d %u %u %d %u %s\n", client->id,
        client->position->x, client->position->y, client->direction + 1,
        client->level, client->team);
}
