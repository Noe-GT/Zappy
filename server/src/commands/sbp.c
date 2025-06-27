/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/sbp.c
*/

#include "../../include/commands.h"

void command_sbp(client_t *client)
{
    send_message(client->fd, "sbp\n");
}
