/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/time.c
*/

#include "../include/server.h"

int calculate_downtime(server_t *server)
{
    if (server->cons == 1)
        return -1;
    return 1000 / server->parameters->freq;
}
