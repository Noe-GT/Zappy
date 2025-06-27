/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pfk.c
*/

#include "../../include/commands.h"

void command_pfk(client_t *client)
{
    send_message(client->fd, "pfk #%d\n", client->id);
}
