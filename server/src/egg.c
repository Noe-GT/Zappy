/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/egg.c
*/

#include <string.h>

#include "../include/server.h"
#include "../include/game.h"
#include "../include/client.h"

void new_egg(server_t *server, char *team)
{
    egg_t *new = (egg_t *)malloc(sizeof(egg_t));

    new->team = team;
    new->id = server->egg_count;
    ++server->egg_count;
    new->next = server->egg;
    new->position = (vector2_t *)malloc(sizeof(vector2_t));
    new->position->x = rand() % MAP->width;
    new->position->y = rand() % MAP->height;
    new->direction = rand() % 4;
    server->egg = new;
}

void new_egg_position(server_t *server, char *team, vector2_t *position)
{
    egg_t *new = (egg_t *)malloc(sizeof(egg_t));

    new->team = team;
    new->id = server->egg_count;
    ++server->egg_count;
    new->next = server->egg;
    new->position = (vector2_t *)malloc(sizeof(vector2_t));
    new->position->x = position->x;
    new->position->y = position->y;
    new->direction = rand() % 4;
    server->egg = new;
}

static void remove_egg(egg_t **head, egg_t *to_remove, egg_t *prev)
{
    if (prev == NULL)
        *head = to_remove->next;
    else
        prev->next = to_remove->next;
}

egg_t *pop_egg(egg_t **egg, char *team)
{
    egg_t *prev = NULL;

    for (egg_t *curr = *egg; curr != NULL; curr = curr->next) {
        if (strcmp(curr->team, team) == 0) {
            remove_egg(egg, curr, prev);
            return curr;
        }
        prev = curr;
    }
    return NULL;
}

size_t count_eggs(egg_t *egg, char *team)
{
    if (egg == NULL)
        return 0;
    if (strcmp(egg->team, team) == 0)
        return 1 + count_eggs(egg->next, team);
    return 0 + count_eggs(egg->next, team);
}

bool replace_egg(server_t *server, client_t *client)
{
    egg_t *egg = pop_egg(&server->egg, client->team);

    if (egg == NULL)
        return false;
    client->position = egg->position;
    client->direction = egg->direction;
    client->id = server->player_count;
    printf("player count %d\n", client->id);
    ++server->player_count;
    crack_egg(egg);
    return true;
}
