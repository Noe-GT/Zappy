/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/egg_utils.c
*/

#include "../include/game.h"

// I know it's useless, but just in case I need to free other things
// Also the name is funny.
void crack_egg(egg_t *egg)
{
    free(egg);
}

void destroy_eggs(egg_t *egg)
{
    if (egg == NULL)
        return;
    destroy_eggs(egg->next);
    crack_egg(egg);
}
