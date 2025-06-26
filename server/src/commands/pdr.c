/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pdr.c
*/

#include "../../include/commands.h"

// TODO: resource number
void command_pdr(client_t *client)
{
    send_message(client->fd, "pdr #%d i\n");
}
