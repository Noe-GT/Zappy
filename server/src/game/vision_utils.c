/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/game/vision_utils.c
*/

#include "../../include/server.h"

void out_of_bound(server_t *server, int *x, int *y)
{
    int diff = 0;

    if (*x < 0)
        *x = PARAMETERS->width + *x;
    if (*x > PARAMETERS->width - 1) {
        diff = *x - PARAMETERS->width;
        *x = 0 + diff;
    }
    if (*y < 0)
        *y = PARAMETERS->height + *y;
    if (*y > PARAMETERS->height - 1) {
        diff = *y - PARAMETERS->height;
        *y = 0 + diff;
    }
}
