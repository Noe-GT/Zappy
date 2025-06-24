/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/seg.c
*/

#include "../../include/commands.h"

void command_seg(client_t *client, char *team)
{
    send_message(client->fd, "seg %s\n", team);
}
