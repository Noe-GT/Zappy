/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/broadcast.c
*/

#include "../../include/commands.h"

static uint32_t calc_wrap_dist(uint32_t from, uint32_t to, uint16_t size)
{
    return (to >= from) ? (to - from) : (size - from + to);
}

static direction_t broadcast_direction(vector2_t *from, vector2_t *to,
    uint16_t width, uint16_t height)
{
    uint32_t dx_right = calc_wrap_dist(from->x, to->x, width);
    uint32_t dx_left = calc_wrap_dist(to->x, from->x, width);
    uint32_t dy_down = calc_wrap_dist(from->y, to->y, height);
    uint32_t dy_up = calc_wrap_dist(to->y, from->y, height);
    uint32_t min_dist = dx_right;
    direction_t result = RIGHT;

    if (from->x == to->x && from->y == to->y)
        return -1;
    if (dx_left < min_dist) {
        min_dist = dx_left;
        result = LEFT;
    }
    if (dy_down < min_dist) {
        min_dist = dy_down;
        result = DOWN;
    }
    return dy_up < min_dist ? UP : result;
}

void command_broadcast(server_t *server, client_t *client, char *message)
{
    char *text = message + strlen("broadcast ");

    for (uint64_t i = 0; i < server->cons - 1; ++i) {
        if (server->clients[i]->id == client->id) {
            command_ok(client->fd);
            continue;
        }
        if (server->clients[i]->is_ai)
            send_message(server->clients[i]->fd, "message %d, %s\n",
                broadcast_direction(server->clients[i]->position,
                client->position, server->parameters->width,
                server->parameters->height) + 1, text);
        if (server->clients[i]->is_gui)
            command_pbc(server->clients[i], "pbc #%d %s\n", client->id, text);
    }
}
