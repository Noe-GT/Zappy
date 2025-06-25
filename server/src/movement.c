/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/movement.c
*/

#include "../include/server.h"

static size_t player_index(tile_t *tile, client_t *client)
{
    for (size_t i = 0; i < tile->player_count; ++i) {
        if (tile->players[i]->id == client->id)
            return i;
    }
    return 0;
}

void add_player_tile(server_t *server, client_t *client, vector2_t *position)
{
    tile_t tile = server->map->tiles[client->position->y][client->position->x];

    tile.players = realloc(tile.players, sizeof(client_t *)
        * (tile.player_count + 1));
    tile.players[tile.player_count] = client;
    ++tile.player_count;
}

void remove_player_tile(server_t *server, client_t *client,
    vector2_t *position)
{
    tile_t tile = server->map->tiles[client->position->y][client->position->x];
    size_t index = player_index(&tile, client);

    if (index == tile.player_count - 1) {
        tile.players[index] = NULL;
        tile.players = realloc(tile.players, sizeof(client_t *)
            * (tile.player_count - 1));
    } else {
        for (size_t i = index; i < tile.player_count - 1; ++i) {
            tile.players[i] = tile.players[i + 1];
        }
        tile.players = realloc(tile.players, sizeof(client_t *)
            * (tile.player_count - 1));
    }
    --tile.player_count;
}
