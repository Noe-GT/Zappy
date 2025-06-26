/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/game/elevation.c
*/

#include "../../include/server.h"
#include "../../include/commands.h"

static bool tile_has_required_resources(tile_t *tile, int level)
{
    if (level < 1 || level > 7)
        return false;
    for (int i = 0; i < RESOURCE_TYPES; ++i) {
        if (tile->resources[i] < elevation_requirements[level - 1][i])
            return false;
    }
    return true;
}

static void remove_elevation_resources_from_tile(tile_t *tile, int level)
{
    for (int i = 0; i < RESOURCE_TYPES; ++i)
        tile->resources[i] -= elevation_requirements[level - 1][i];
}

static bool count_players_on_map(server_t *server, int level)
{
    int count = 0;
    int required = elevation_requirements[level - 1][0];

    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (server->clients[i] && server->clients[i]->level ==
            level && server->clients[i]->is_ai)
            ++count;
    }
    return (count >= required);
}

void elevate_players(tile_t *tile, server_t *server,
    client_t *client, int level)
{
    int required_players = elevation_requirements[level - 1][0];
    int present_players_map = count_players_on_map(server, level);

    if (present_players_map < required_players) {
        command_ko(client->fd);
        return;
    }
    if (!tile_has_required_resources(tile, level)) {
        command_ko(client->fd);
        return;
    }
    for (size_t i = 0; i < tile->player_count; ++i) {
        if (tile->players[i] && tile->players[i]->level == level) {
            ++tile->players[i]->level;
            tile->players[i]->is_elevating = false;
        }
    }
    remove_elevation_resources_from_tile(tile, level);
}
