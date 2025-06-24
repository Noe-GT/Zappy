/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pgt.c
*/

#include "../../include/commands.h"

// TODO: resource number
void command_pgt(client_t *client)
{
    send_message(client->fd, "pgt #%d i\n", client->id);
}
