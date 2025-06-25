/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/forward.c
*/

#include "../../include/commands.h"

static void fuck_it(server_t *server, client_t *client, vector2_t *old)
{
    remove_player_tile(server, client, old);
    add_player_tile(server, client, client->position);
    command_ok(client->fd);
}

void command_forward(server_t *server, client_t *client, char *message)
{
    vector2_t old = {.x = client->position->x, .y = client->position->y};

    (void)message;
    if (client->direction == UP) {
        if (client->position->y == 0)
            client->position->y = server->parameters->height - 1;
        else
            client->position->y -= 1;
    } else if (client->direction == DOWN)
        client->position->y = client->position->y + 1
            % server->parameters->height;
    if (client->direction == LEFT) {
        if (client->position->x == 0)
            client->position->x = server->parameters->width - 1;
        else
            client->position->x -= 1;
    } else if (client->direction == RIGHT)
        client->position->x = client->position->x + 1
            % server->parameters->width;
    fuck_it(server, client, &old);
}
