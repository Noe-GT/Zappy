/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_
    #include "external.h"

typedef struct player_s {
    int id;
} player_t;

typedef struct map_tile_s {
    player_t **players;
} map_tile_t;

typedef struct map_s {
    size_t tiles_x;
    size_t tiles_y;
    map_tile_t **tiles;
} map_t;

typedef struct game_s {
    map_t map;
} game_t;

#endif /* !GAME_H_ */
