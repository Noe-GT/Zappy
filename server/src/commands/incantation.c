/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/game/elevation.c
*/

#include "../../include/server.h"
#include "../../include/commands.h"

static bool has_required_resources(server_t *server, client_t *client)
{
    int level = client->level;
    tile_t *tile = &server->map->tiles[client->position->y]
        [client->position->x];

    if (level < 1 || level > 7)
        return false;
    for (int i = 0; i < RESOURCE_TYPES; ++i) {
        if (tile->resources[i] < elevation_requirements[4][i])
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

bool can_start_incantation(server_t *server, client_t *client)
{
    int required_players = elevation_requirements[client->level - 1][0];
    int present_players_map = count_players_on_map(server, client->level);

    if (present_players_map < required_players)
        return true;
    if (!has_required_resources(server, client))
        return true;
    return false;
}

void elevate_players(tile_t *tile, server_t *server, client_t *client)
{
    if (!can_start_incantation(server, client))
        return command_ko(client->fd);
    for (size_t i = 0; i < tile->player_count; ++i) {
        if (tile->players[i] && tile->players[i]->level == client->level) {
            ++tile->players[i]->level;
            tile->players[i]->is_elevating = false;
        }
    }
    remove_elevation_resources_from_tile(tile, client->level);
}

void command_incantation(server_t *server, client_t *client, char *message)
{
    tile_t *tile = &server->map->tiles[client->position->y]
        [client->position->x];

    (void)message;
    elevate_players(tile, server, client);
    command_pie(server, client, true);
    server_plv(server, client);
}

void command_pre_incantation(client_t *client)
{
    send_message(client->fd, "Elevation underway\nCurrent level: %d\n",
        client->level);
}
