/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/parser/parser.c
*/

#include "../../include/server.h"
#include "../../include/utils.h"

#include <string.h>
#include <stdbool.h>

static bool handle_other_short_flag(char **av, int *i,
    int ac, server_t *server)
{
    if (strcmp(av[*i], "-p") == 0) {
        parse_port(server, av + *i, ac - *i);
        ++(*i);
        PARAMETERS->required->port = true;
        return true;
    }
    if (strcmp(av[*i], "-x") == 0) {
        parse_width(server, av + *i, ac - *i);
        ++(*i);
        PARAMETERS->required->width = true;
        return true;
    }
    if (strcmp(av[*i], "-y") == 0) {
        parse_height(server, av + *i, ac - *i);
        ++(*i);
        PARAMETERS->required->height = true;
        return true;
    }
    return false;
}

void count_team(int ac, char **av, server_t *server, int *i)
{
    PARAMETERS->team_count = 0;
    for (int j = *i + 1; j < ac && av[j][0] != '-'; ++j)
        ++PARAMETERS->team_count;
}

void get_names(server_t *server, char **av, int ac, int *i)
{
    int j = 0;

    count_team(ac, av, server, i);
    PARAMETERS->team_names = NULL;
    if (PARAMETERS->team_count < 2)
        usage("You must provide at least 2 teams after -n");
    PARAMETERS->team_names = malloc(sizeof(char *) * PARAMETERS->team_count);
    for (; j < PARAMETERS->team_count; ++j) {
        PARAMETERS->team_names[j] = strdup(av[*i + j + 1]);
    }
    *i += j;
}

static bool handle_short_flag(char **av, int *i, int ac, server_t *server)
{
    if (strcmp(av[*i], "-c") == 0) {
        parse_nb_clients(server, av + *i, ac - *i);
        ++(*i);
        PARAMETERS->required->clients = true;
        return true;
    }
    if (strcmp(av[*i], "-f") == 0) {
        parse_freq(server, av + *i, ac - *i);
        ++(*i);
        return true;
    }
    if (strcmp(av[*i], "-n") == 0) {
        get_names(server, av, ac, i);
        PARAMETERS->required->teams = true;
        return true;
    }
    return false;
}

static void parse_long_flag(char **av, int *i, int ac, server_t *server)
{
    if (strcmp(av[*i], "--auto-start") == 0) {
        parse_auto_start(server, av + *i, ac - *i);
        ++(*i);
        return;
    }
    if (strcmp(av[*i], "--display-eggs") == 0) {
        parse_display_egg(server, av + *i, ac - *i);
        ++(*i);
        return;
    }
    if (strcmp(av[*i], "--match_duration") == 0) {
        parse_match_duration(server, av + *i, ac - *i);
        ++(*i);
        return;
    }
    if (strcmp(av[*i], "--verbose") == 0 || strcmp(av[*i], "-v") == 0) {
        PARAMETERS->verbose = true;
        return;
    }
    usage("Incorrect Arguments");
}

static void check_required_flags(required_flags_t *flags)
{
    if (!flags->port)
        usage("Missing -p (port) flag");
    if (!flags->width)
        usage("Missing -x (width) flag");
    if (!flags->height)
        usage("Missing -y (height) flag");
    if (!flags->teams)
        usage("Missing -n (team names) flag");
    if (!flags->clients)
        usage("Missing -c (clientsNb) flag");
}

static void parse_flag(char **av, int *i, int ac, server_t *server)
{
    if (handle_short_flag(av, i, ac, server) ||
        handle_other_short_flag(av, i, ac, server))
        return;
    parse_long_flag(av, i, ac, server);
}

void parser(int ac, char **av, server_t *server)
{
    server->parameters = malloc(sizeof(parameters_t));
    server->parameters->required = malloc(sizeof(parameters_t));
    server->ticks = 0;
    server->tick_timer = 0;
    server->egg_count = 0;
    server->egg = NULL;
    server->end = false;
    for (int i = 1; i < ac; ++i)
        parse_flag(av, &i, ac, server);
    check_required_flags(PARAMETERS->required);
}
