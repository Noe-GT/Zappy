/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/game/elevation.c
*/

#include "../../include/server.h"

static bool has_required_resources(client_t *client, int level)
{
    if (level < 1 || level > 7)
        return true;
    for (int i = 1; i < RESOURCE_TYPES; ++i)
        if (client->inventory[i] < elevation_requirements[level - 1][i])
            return true;
    return false;
}

static void remove_elevation_resources(client_t *client, int level)
{
    for (int i = 1; i < RESOURCE_TYPES; ++i)
        client->inventory[i] -= elevation_requirements[level - 1][i];
}

static bool number_players_level(server_t *server, int level)
{
    int count = 0;
    int required = elevation_requirements[level - 1][0];

    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (server->clients[i] && server->clients[i]->level == level)
            ++count;
    }
    return (count >= required);
}

void start_elevation(client_t *client, int level)
{
    if (!client->is_elevating) {
        if (has_required_resources(client, level))
            return;
        client->is_elevating = true;
    }
}

void elevation(client_t *client, tile_t *tile, int level)
{
    for (size_t i = 0; i < tile->player_count; ++i) {
        if (tile->players[i]->level == level &&
            tile->players[i]->is_elevating) {
            ++tile->players[i]->level;
            tile->players[i]->is_elevating = false;
            remove_elevation_resources(tile->players[i], level);
        }
        if (tile->players[i]->level == level) {
            start_elevation(client, level);
        }
    }
}

void elevate_players(tile_t *tile, server_t *server,
    client_t *client, int level)
{
    if (!number_players_level(server, level))
        return;
    elevation(client, tile, level);
}
