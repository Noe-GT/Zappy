/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/aic.c
*/

#include "../../include/commands.h"

// add_player_tile should be done when the egg is placed
void command_aic(server_t *server, client_t *client)
{
    uint16_t count = count_team_members(server, client->team);

    if (PARAMETERS->nb_clients - count == 0)
        return command_ko(client->fd);
    else
        send_message(client->fd, "%d\n%u %u\n", PARAMETERS->nb_clients - count,
            PARAMETERS->width, PARAMETERS->height);
    add_player_tile(server, client, client->position);
}
