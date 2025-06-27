/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/egg_utils.c
*/

#include "../include/game.h"
#include "../include/commands.h"

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

static bool egg_exists(egg_t *egg, vector2_t *position)
{
    if (egg == NULL)
        return false;
    if (egg->position->x == position->x && egg->position->y == position->y)
        return true;
    return egg_exists(egg->next, position);
}

static void remove_egg(egg_t **head, egg_t *to_remove, egg_t *prev)
{
    if (prev == NULL)
        *head = to_remove->next;
    else
        prev->next = to_remove->next;
}

static egg_t *pop_egg_pos(egg_t **egg, vector2_t *position)
{
    egg_t *prev = NULL;

    for (egg_t *curr = *egg; curr != NULL; curr = curr->next) {
        if (curr->position->x == position->x &&
            curr->position->y == position->y) {
            remove_egg(egg, curr, prev);
            return curr;
        }
        prev = curr;
    }
    return NULL;
}

void eject_eggs(egg_t **head, server_t *server, vector2_t *position)
{
    egg_t *egg = NULL;

    while (egg_exists(*head, position)) {
        egg = pop_egg_pos(head, position);
        command_edi(server, egg);
        crack_egg(egg);
    }
}
