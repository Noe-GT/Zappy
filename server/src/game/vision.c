/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/game/vision.c
*/

#include "../../include/server.h"

#include <stdlib.h>
#include <string.h>

static void get_vision_coordinates(client_t *client, size_t y,
    int *xw, int *yw)
{
    int offset = 2 * (y + 1) + 1;

    switch (client->direction) {
        case UP:
            *yw = client->position->y + 1 + y;
            *xw = client->position->x - (offset / 2);
            break;
        case RIGHT:
            *yw = client->position->y - (offset / 2);
            *xw = client->position->x + 1 + y;
            break;
        case LEFT:
            *yw = client->position->y + (offset / 2);
            *xw = client->position->x - 1 - y;
            break;
        case DOWN:
            *yw = client->position->y - 1 - y;
            *xw = client->position->x + (offset / 2);
            break;
    }
}

static void out_of_bound(server_t *server, int *x, int *y)
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

static void append_resources(char *buffer, int buffer_size,
    int *len)
{
    if (*len > 0)
        *len += snprintf(buffer + *len, buffer_size - *len, " ");
}

static void append_players_and_eggs(server_t *server, tile_t *tile, vector2_t pos, char *buffer)
{
    int len = strlen(buffer);

    for (size_t p = 0; p < tile->player_count; ++p) {
        append_resources(buffer, 256, &len);
        len += snprintf(buffer + len, 256 - len, "player");
    }
    for (egg_t *egg = server->egg; egg != NULL; egg = egg->next) {
        if (egg->position->x == pos.x && egg->position->y == pos.y) {
            append_resources(buffer, 256, &len);
            len += snprintf(buffer + len, 256 - len, "egg");
        }
    }
    buffer[len] = '\0';
}

static char *get_tile_content(server_t *server, int x, int y)
{
    char *names[RESOURCE_TYPES] = {
        "food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"
    };
    char *buffer = malloc(256);
    int len = 0;
    tile_t *tile = &MAP->tiles[y][x];
    vector2_t pos = {x, y};

    buffer[0] = '\0';
    out_of_bound(server, &x, &y);
    append_players_and_eggs(server, tile, pos, buffer);
    len = strlen(buffer);
    for (int i = 0; i < RESOURCE_TYPES; ++i) {
        for (int j = 0; j < tile->resources[i]; ++j) {
            append_resources(buffer, 256, &len);
            len += snprintf(buffer + len, 256 - len, "%s", names[i]);
        }
    }
    return buffer;
}

char *get_content(client_t *client, server_t *server, int x, int y)
{
    int yw = 0;
    int xw = 0;
    char *content;

    get_vision_coordinates(client, y, &xw, &yw);
    if (client->direction == UP)
        content = get_tile_content(server, xw + x, yw - (2 * y + 2));
    if (client->direction == RIGHT)
        content = get_tile_content(server, xw, yw + x);
    if (client->direction == LEFT)
        content = get_tile_content(server, xw, yw - x);
    if (client->direction == DOWN)
        content = get_tile_content(server, xw + x, yw + (y * 2 + 2));
    return content;
}

static void append_content(char *result, int *len, char *content, bool is_last)
{
    if (is_last)
        *len += snprintf(result + *len, 4096 - *len, "%s]", content);
    else
        *len += snprintf(result + *len, 4096 - *len, "%s, ", content);
}

static bool is_last_tile(client_t *client, int y, int x)
{
    return (y == client->level - 1 && x == (2 * (y + 1)));
}

char *handle_vision(server_t *server, client_t *client)
{
    char *result = malloc(4096);
    char *content;
    int len = 0;

    result[0] = '\0';
    if (!client->position)
        return strdup("[]");
    content = get_content(client, server,
        client->position->x, client->position->y);
    len += snprintf(result + len, 4096 - len, "[%s, ", content);
    free(content);
    for (size_t y = 0; y < client->level; ++y) {
        for (size_t x = 0; x < (2 * (y + 1) + 1); ++x) {
            content = get_content(client, server, x, y);
            append_content(result, &len, content, is_last_tile(client, y, x));
            free(content);
        }
    }
    return result;
}
