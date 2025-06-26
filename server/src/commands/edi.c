/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/edi.c
*/

#include "../../include/commands.h"

void command_edi(client_t *client, uint32_t egg_number)
{
    send_message(client->fd, "edi #%u\n", egg_number);
}
