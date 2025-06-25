/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/time.c
*/

#include <time.h>

#include "../include/server.h"

int calculate_downtime(server_t *server)
{
    if (server->cons == 1)
        return -1;
    return 1000 / server->parameters->freq;
}

uint64_t get_time_milliseconds(void)
{
    struct timespec spec;

    clock_gettime(1, &spec);
    return spec.tv_sec * 1000 + spec.tv_nsec / 1e6;
}
