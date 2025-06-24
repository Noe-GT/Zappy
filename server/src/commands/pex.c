/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pex.c
*/

#include "../../include/commands.h"

// Go back to your country
void command_pex(client_t *client)
{
    send_message(client->fd, "pex #%d\n", client->id);
}
