/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <stdlib.h>
    #include <stdbool.h>
    #include "vector.h"

    #define RESOURCE_TYPES 7

    #define MAP server->map

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

typedef struct egg_s {
    int id;
    char *team;
    vector2_t *position;
    direction_t direction;
    struct egg_s *next;
} egg_t;

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

typedef struct server_s server_t;

typedef struct client_s client_t;

void new_egg(server_t *server, char *team);
egg_t *pop_egg(egg_t **egg, char *team);
size_t count_eggs(egg_t *egg, char *team);
bool replace_egg(server_t *server, client_t *client);
void new_egg_position(server_t *server, char *team, vector2_t *position);
void crack_egg(egg_t *egg);
void destroy_eggs(egg_t *egg);

#endif /* !GAME_H_ */
