/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/movement.c
*/

#include "../include/server.h"

static size_t player_index(tile_t *tile, client_t *client)
{
    printf("client id %d - pos x(%u) y(%u)\n", client->id,
        client->position->x, client->position->y);
    for (size_t i = 0; i < tile->player_count; ++i) {
        printf("tile %lu\n", tile->player_count);
        printf("player id %d\n", tile->players[i]->id);
        if (tile->players[i]->id == client->id)
            return i;
    }
    return 0;
}

void add_player_tile(server_t *server, client_t *client, vector2_t *position)
{
    tile_t *tile = &server->map->tiles[position->y][position->x];

    tile->players = realloc(tile->players, sizeof(client_t *)
        * (tile->player_count + 1));
    tile->players[tile->player_count] = client;
    ++tile->player_count;
}

static void realloc_tile(tile_t *tile)
{
    if (tile->player_count != 1)
        tile->players = realloc(tile->players, sizeof(client_t *)
            * (tile->player_count - 1));
    else {
        free(tile->players);
        tile->players = NULL;
    }
}

void remove_player_tile(server_t *server, client_t *client,
    vector2_t *position)
{
    tile_t *tile = &server->map->tiles[position->y][position->x];
    size_t index = player_index(tile, client);

    if (index == tile->player_count - 1) {
        tile->players[index] = NULL;
        realloc_tile(tile);
    } else {
        for (size_t i = index; i < tile->player_count - 1; ++i)
            tile->players[i] = tile->players[i + 1];
        realloc_tile(tile);
    }
    --tile->player_count;
}

void forward(server_t *server, client_t *client)
{
    if (client->direction == UP) {
        if (client->position->y == 0)
            client->position->y = server->parameters->height - 1;
        else
            client->position->y -= 1;
    } else if (client->direction == DOWN)
        client->position->y = (client->position->y + 1)
            % server->parameters->height;
    if (client->direction == LEFT) {
        if (client->position->x == 0)
            client->position->x = server->parameters->width - 1;
        else
            client->position->x -= 1;
    } else if (client->direction == RIGHT)
        client->position->x = (client->position->x + 1)
            % server->parameters->width;
}

void move_player(server_t *server, client_t *client, direction_t direction)
{
    if (direction == UP) {
        if (client->position->y == 0)
            client->position->y = server->parameters->height - 1;
        else
            client->position->y -= 1;
    } else if (direction == DOWN)
        client->position->y = (client->position->y + 1)
            % server->parameters->height;
    if (direction == LEFT) {
        if (client->position->x == 0)
            client->position->x = server->parameters->width - 1;
        else
            client->position->x -= 1;
    } else if (direction == RIGHT)
        client->position->x = (client->position->x + 1)
            % server->parameters->width;
}
