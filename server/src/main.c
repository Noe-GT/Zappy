/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/main.c
*/

#include "../include/server.h"

#include <time.h>

static void create_start_team_eggs(server_t *server)
{
    for (uint16_t i = 0; i < PARAMETERS->team_count; ++i) {
        for (size_t j = 0; j < PARAMETERS->nb_clients; ++j) {
            new_egg(server, PARAMETERS->team_names[i]);
        }
    }
}

static void initialize_map(server_t *server)
{
    server->map = (map_t *)malloc(sizeof(map_t));
    if (!server->map)
        exit(84);
    init_map(MAP, PARAMETERS->width, PARAMETERS->height);
}

int main(int ac, char **av)
{
    server_t server = {0};

    srand(time(NULL));
    parser(ac, av, &server);
    initialize_map(&server);
    handle_ressource(&server);
    create_start_team_eggs(&server);
    run_server(&server);
}
