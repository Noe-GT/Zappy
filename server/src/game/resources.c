/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/game/resources.c
*/

#include "../../include/server.h"

#include <string.h>
#include <stdlib.h>

void init_map(map_t *map, size_t width, size_t height)
{
    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(tile_t *) * height);
    for (size_t y = 0; y < height; ++y) {
        map->tiles[y] = malloc(sizeof(tile_t) * width);
        for (size_t x = 0; x < width; ++x) {
            memset(map->tiles[y][x].resources, 0,
                sizeof(int) * RESOURCE_TYPES);
            map->tiles[y][x].players = NULL;
            map->tiles[y][x].player_count = 0;
        }
    }
}

void free_map(map_t *map)
{
    for (size_t y = 0; y < map->height; ++y) {
        for (size_t x = 0; x < map->width; ++x) {
            free(map->tiles[y][x].players);
        }
        free(map->tiles[y]);
    }
    free(map->tiles);
}

static void count_resources(server_t *server, int *current)
{
    size_t nb_tiles = MAP->width * MAP->height;
    size_t x = 0;
    size_t y = 0;

    memset(current, 0, sizeof(int) * RESOURCE_TYPES);
    for (size_t i = 0; i < nb_tiles; ++i) {
        y = i / MAP->width;
        x = i % MAP->width;
        for (int j = 0; j < RESOURCE_TYPES; ++j)
            current[j] += MAP->tiles[y][x].resources[j];
    }
}

static void get_required(server_t *server, int *required)
{
    size_t nb_tiles = MAP->width * MAP->height;

    for (int i = 0; i < RESOURCE_TYPES; ++i)
        required[i] = (int)(nb_tiles * resource_densities[i]);
}

static void respawn_resources(server_t *server, int *required, int *current)
{
    int add = 0;
    size_t x;
    size_t y;

    for (int i = 0; i < RESOURCE_TYPES; ++i) {
        add = required[i] - current[i];
        for (; add > 0; --add) {
            x = rand() % MAP->width;
            y = rand() % MAP->height;
            MAP->tiles[y][x].resources[i]++;
        }
    }
}

static void print_resource_diff(const char *name, int diff, int *first)
{
    if (diff > 0) {
        if (!*first)
            printf(", ");
        printf("%s=%d", name, diff);
        *first = 0;
    }
}

void print_respawned_resources(int *required, int *current)
{
    const char *names[RESOURCE_TYPES] = {
        "food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"
    };
    int first = 1;
    int diff = 0;

    printf("[Resource Respawn] Added: ");
    for (int i = 0; i < RESOURCE_TYPES; ++i) {
        diff = required[i] - current[i];
        print_resource_diff(names[i], diff, &first);
    }
    if (first)
        printf("none");
    printf("\n");
}

void handle_ressource(server_t *server)
{
    int required[RESOURCE_TYPES] = {0};
    int current[RESOURCE_TYPES] = {0};

    get_required(server, required);
    count_resources(server, current);
    respawn_resources(server, required, current);
    print_respawned_resources(required, current);
}
