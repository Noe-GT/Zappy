/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/main.c
*/

#include "../include/server.h"

int main(int ac, char **av)
{
    server_t server;

    parser(ac, av, &server);
    // server_t *server = init_server(20);
    //
    // if (server == NULL)
    //     return 84;
    // server_run(server);
    // free_server(server);
    // return 0;
}
