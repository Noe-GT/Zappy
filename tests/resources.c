/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** tests/resources.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>

#include "../server/include/server.h"

Test(resources, respawn_resources)
{
    server_t server = {0};
    server.parameters = malloc(sizeof(parameters_t));
    server.parameters->width = 5;
    server.parameters->height = 5;
    server.game = malloc(sizeof(game_t));

    init_map(&server.game->map, server.parameters->width, server.parameters->height);

    for (size_t y = 0; y < server.game->map.height; ++y)
        for (size_t x = 0; x < server.game->map.width; ++x)
            for (int i = 0; i < RESOURCE_TYPES; ++i)
                server.game->map.tiles[y][x].resources[i] = 0;

    handle_ressource(&server);

    int total[RESOURCE_TYPES] = {0};

    for (size_t y = 0; y < server.game->map.height; ++y)
        for (size_t x = 0; x < server.game->map.width; ++x)
            for (int i = 0; i < RESOURCE_TYPES; ++i)
                total[i] += server.game->map.tiles[y][x].resources[i];

    for (int i = 0; i < RESOURCE_TYPES; ++i)
        cr_assert(total[i] > 0, "Resource %d should have respawned on the map", i);

    free_map(&server.game->map);
    free(server.game);
    free(server.parameters);
}

Test(resources, no_respawn_when_enough)
{
    server_t server = {0};
    server.parameters = malloc(sizeof(parameters_t));
    server.parameters->width = 5;
    server.parameters->height = 5;
    server.game = malloc(sizeof(game_t));
    init_map(&server.game->map, server.parameters->width, server.parameters->height);

    int required[RESOURCE_TYPES];
    size_t nb_tiles = server.parameters->width * server.parameters->height;
    for (int i = 0; i < RESOURCE_TYPES; ++i)
        required[i] = (int)(nb_tiles * resource_densities[i]);

    for (size_t y = 0; y < server.game->map.height; ++y)
        for (size_t x = 0; x < server.game->map.width; ++x)
            for (int i = 0; i < RESOURCE_TYPES; ++i)
                server.game->map.tiles[y][x].resources[i] = required[i] + 5;

    int before[RESOURCE_TYPES] = {0};

    for (size_t y = 0; y < server.game->map.height; ++y)
        for (size_t x = 0; x < server.game->map.width; ++x)
            for (int i = 0; i < RESOURCE_TYPES; ++i)
                before[i] += server.game->map.tiles[y][x].resources[i];

    handle_ressource(&server);

    int after[RESOURCE_TYPES] = {0};

    for (size_t y = 0; y < server.game->map.height; ++y)
        for (size_t x = 0; x < server.game->map.width; ++x)
            for (int i = 0; i < RESOURCE_TYPES; ++i)
                after[i] += server.game->map.tiles[y][x].resources[i];

    for (int i = 0; i < RESOURCE_TYPES; ++i)
        cr_assert_eq(after[i], before[i], "Resource %d should not have increased if already enough", i);

    free_map(&server.game->map);
    free(server.game);
    free(server.parameters);
}
