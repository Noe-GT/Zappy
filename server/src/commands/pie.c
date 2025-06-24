/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pie.c
*/

#include "../../include/commands.h"

void command_pie(client_t *client)
{
    send_message(client->fd, "pie %u %u %d\n", client->position->x,
        client->position->y, client->level + 1);
}
