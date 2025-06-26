/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/nbr.c
*/

#include "../../include/commands.h"

void command_nbr(server_t *server, client_t *client, char *message)
{
    uint16_t count = count_eggs(server->egg, client->team);

    (void)message;
    send_message(client->fd, "%d\n", PARAMETERS->nb_clients - count);
}
