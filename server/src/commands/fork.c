/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/fork.c
*/

#include "../../include/commands.h"

void command_fork(server_t *server, client_t *client, char *message)
{
    (void)message;
    new_egg(server, client->team);
    command_enw(server, client, server->egg);
}
