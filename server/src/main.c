/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/main.c
*/

#include "../include/server.h"

int main(int ac, char **av)
{
    server_t server = {0};

    parser(ac, av, &server);
    init_server(&server);
    if (server.network == NULL)
        return 84;
    server_run(&server);
    free_server(&server);
}
