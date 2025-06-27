/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/forward.c
*/

#include "../../include/commands.h"

void command_forward(server_t *server, client_t *client, char *message)
{
    vector2_t old = {.x = client->position->x, .y = client->position->y};

    (void)message;
    forward(server, client);
    remove_player_tile(server, client, &old);
    add_player_tile(server, client, client->position);
    command_ok(client->fd);
}
