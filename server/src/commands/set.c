/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/set.c
*/

#include "../../include/commands.h"

static void set_resource(server_t *server, client_t *client, int resid)
{
    if (client->inventory[resid] > 0) {
        --client->inventory[resid];
        ++TILE.resources[resid];
        command_pdr(server, client, resid);
        return command_ok(client->fd);
    } else {
        return command_ko(client->fd);
    }
}

void command_set(server_t *server, client_t *client, char *message)
{
    char *object = message + strlen("set ");

    if (strcmp(object, "food\n") == 0)
        return set_resource(server, client, FOOD);
    if (strcmp(object, "linemate\n") == 0)
        return set_resource(server, client, LINEMATE);
    if (strcmp(object, "deraumere\n") == 0)
        return set_resource(server, client, DERAUMERE);
    if (strcmp(object, "sibur\n") == 0)
        return set_resource(server, client, SIBUR);
    if (strcmp(object, "mendiane\n") == 0)
        return set_resource(server, client, MENDIANE);
    if (strcmp(object, "phiras\n") == 0)
        return set_resource(server, client, PHIRAS);
    if (strcmp(object, "thystame\n") == 0)
        return set_resource(server, client, THYSTAME);
    command_ko(client->fd);
}
