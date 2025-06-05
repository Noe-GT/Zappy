/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/parser/parse_end.c
*/

#include "../../include/server.h"
#include "../../include/utils.h"

void parse_auto_start(server_t *server, char **av, int len)
{
    bool error = true;

    if (len <= 1)
        usage("Auto Start is not specified");
    if (strlen(av[1]) == 2 || strlen(av[1]) == 3) {
        if (strcmp(av[1], "on") == 0) {
            PARAMETERS->auto_start = true;
            error = false;
        }
        if (strcmp(av[1], "off") == 0) {
            PARAMETERS->auto_start = false;
            error = false;
        }
    }
    if (error)
        usage("Auto Start is not correctly specified");
}

void parse_display_egg(server_t *server, char **av, int len)
{
    bool error = true;

    if (len <= 1)
        usage("Display Eggs is not specified");
    if (strlen(av[1]) == 4 || strlen(av[1]) == 5) {
        if (strcmp(av[1], "true") == 0) {
            PARAMETERS->display_egg = true;
            error = false;
        }
        if (strcmp(av[1], "false") == 0) {
            PARAMETERS->display_egg = false;
            error = false;
        }
    }
    if (error)
        usage("Display Egg is not correctly specified");
}

void parse_match_duration(server_t *server, char **av, int len)
{
    char *raw_duration = av[1];

    if (len <= 1)
        usage("Match Duration is not specified");
    if (!is_number(raw_duration))
        usage("Match Duration is not a valid number");
    PARAMETERS->match_duration = atoi(raw_duration);
}
