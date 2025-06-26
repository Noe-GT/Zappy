/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/enw.c
*/

#include "../../include/commands.h"

void command_enw(client_t *client, uint32_t egg_number, vector2_t *position)
{
    send_message(client->fd, "enw #%u #%d %u %u", egg_number, client->id,
        position->x, position->y);
}
