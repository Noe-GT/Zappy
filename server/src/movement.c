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
    tile_t tile = server->map->tiles[position->y][position->x];

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

void forward(server_t *server, client_t *client)
{
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
}
