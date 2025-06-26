/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/main.c
*/

#include "../include/server.h"

#include <time.h>

int main(int ac, char **av)
{
    server_t server = {0};

    srand(time(NULL));
    parser(ac, av, &server);
    run_server(&server);
}
