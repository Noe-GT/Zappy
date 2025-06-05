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

    for (int i = 0; i < server.parameters->team_count; ++i)
        free(server.parameters->team_names[i]);
    free(server.parameters->team_names);
    free(server.parameters);

    // server.network = init_network(20);

    // server_t *server = init_server(20);
    //
    // if (server == NULL)
    //     return 84;
    // server_run(server);
    // free_server(server);
    // return 0;
}
