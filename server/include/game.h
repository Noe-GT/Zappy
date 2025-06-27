/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <stdlib.h>

    #define RESOURCE_TYPES 7

    #define MAP server->map
    #define CLIENT server->network->client_list

typedef enum resource_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} resource_t;

typedef struct tile_s {
    int resources[RESOURCE_TYPES];
    struct client_s **players;
    size_t player_count;
} tile_t;

typedef struct map_s {
    size_t width;
    size_t height;
    tile_t **tiles;
} map_t;

static const float resource_densities[RESOURCE_TYPES] = {
    0.5,    // Food
    0.3,    // Linemate
    0.15,   // Deraumere
    0.1,    // Sibur
    0.1,    // Mendiane
    0.08,   // Phiras
    0.05    // Thystame
};

static const int elevation_requirements[7][RESOURCE_TYPES] = {
    {1, 1, 0, 0, 0, 0, 0},  // Level 1 -> Level 2
    {2, 1, 1, 1, 0, 0, 0},  // Level 2 -> Level 3
    {2, 2, 0, 1, 0, 2, 0},  // Level 3 -> Level 4
    {4, 1, 1, 2, 0, 1, 0},  // Level 4 -> Level 5
    {4, 1, 2, 1, 3, 0, 0},  // Level 5 -> Level 6
    {6, 1, 2, 3, 0, 1, 0},  // Level 6 -> Level 7
    {6, 2, 2, 2, 2, 2, 1}   // Level 7 -> Level 8
};

#endif /* !GAME_H_ */
