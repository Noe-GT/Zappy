/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pdi.c
*/

#include "../../include/commands.h"

void command_pdi(client_t *client)
{
    send_message(client->fd, "pdi #%d\n", client->id);
}
