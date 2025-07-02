/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/aic.c
*/

#include "../../include/commands.h"

void command_aic(server_t *server, client_t *client)
{
    uint16_t count = count_eggs(server->egg, client->team) + 1;

    if (count == 0)
        return command_ko(client->fd);
    else
        send_message(client->fd, "%d\n%u %u\n", count,
            PARAMETERS->width, PARAMETERS->height);
    add_player_tile(server, client, client->position);
    command_pnw(server, client);
    server_pin(server, client);
}
