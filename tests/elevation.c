/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** tests/elevation.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>

#include "../server/include/server.h"

Test(elevation, simple_elevation_success)
{
    tile_t tile = {0};
    tile.player_count = 1;
    tile.players = malloc(sizeof(client_t*) * 1);
    tile.players[0] = malloc(sizeof(client_t));
    client_t *client = tile.players[0];
    client->level = 1;
    client->is_elevating = false;

    for (int i = 0; i < RESOURCE_TYPES; ++i)
        client->inventory[i] = elevation_requirements[0][i];

    start_elevation(client, 1);
    elevation(client, &tile, 1);

    cr_assert_eq(client->level, 2, "Player should have leveled up to 2");
    cr_assert_eq(client->is_elevating, false, "Player should not be elevating anymore");
    for (int i = 1; i < RESOURCE_TYPES; ++i)
        cr_assert_eq(client->inventory[i], 0, "Resource %d should be zero after elevation", i);

    free(client);
    free(tile.players);
}

Test(elevation, not_enough_resources)
{
    tile_t tile = {0};
    tile.player_count = 1;
    tile.players = malloc(sizeof(client_t*) * 1);
    tile.players[0] = malloc(sizeof(client_t));
    client_t *client = tile.players[0];
    client->level = 1;
    client->is_elevating = false;

    for (int i = 0; i < RESOURCE_TYPES; ++i)
        client->inventory[i] = 0;

    start_elevation(client, 1);
    elevation(client, &tile, 1);

    cr_assert_eq(client->level, 1, "Player should not have leveled up");
    cr_assert_eq(client->is_elevating, false, "Player should not be elevating anymore");
    for (int i = 1; i < RESOURCE_TYPES; ++i)
        cr_assert_eq(client->inventory[i], 0, "Resource %d should remain zero", i);

    free(client);
    free(tile.players);
}

Test(elevation, not_enough_players_on_map)
{
    server_t server = {0};
    server.cons = 2;
    server.clients = malloc(sizeof(client_t *) * 2);

    tile_t tile = {0};
    tile.player_count = 1;
    tile.players = malloc(sizeof(client_t *) * 1);

    client_t *client = malloc(sizeof(client_t));
    client->level = 2;
    client->is_elevating = false;

    for (int i = 0; i < RESOURCE_TYPES; ++i)
        client->inventory[i] = elevation_requirements[1][i];

    tile.players[0] = client;
    server.clients[0] = client;
    server.clients[1] = NULL;

    elevate_players(&tile, &server, client, 2);

    cr_assert_eq(client->level, 2, "Player should not have leveled up");
    for (int i = 1; i < RESOURCE_TYPES; ++i)
        cr_assert_eq(client->inventory[i], elevation_requirements[1][i], "Resource %d should remain unchanged", i);

    free(client);
    free(tile.players);
    free(server.clients);
}

Test(elevation, enough_players_on_map)
{
    server_t server = {0};
    server.cons = 3;
    server.clients = malloc(sizeof(client_t*) * 3);

    tile_t tile = {0};
    tile.player_count = 2;
    tile.players = malloc(sizeof(client_t*) * 2);

    for (int i = 0; i < 2; ++i) {
        tile.players[i] = malloc(sizeof(client_t));
        tile.players[i]->level = 2;
        tile.players[i]->is_elevating = true;
        for (int j = 0; j < RESOURCE_TYPES; ++j)
            tile.players[i]->inventory[j] = elevation_requirements[1][j];
        server.clients[i] = tile.players[i];
    }
    server.clients[2] = NULL;

    elevate_players(&tile, &server, tile.players[0], 2);

    cr_assert_eq(tile.players[0]->level, 3, "Player 1 should have leveled up to 3");
    cr_assert_eq(tile.players[1]->level, 3, "Player 2 should have leveled up to 3");
    for (int i = 0; i < 2; ++i)
        for (int j = 1; j < RESOURCE_TYPES; ++j)
            cr_assert_eq(tile.players[i]->inventory[j], 0, "Resource %d for player %d should be zero after elevation", j, i);

    free(tile.players[0]);
    free(tile.players[1]);
    free(tile.players);
    free(server.clients);
}
