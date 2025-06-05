/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/parser/parse_start.c
*/

#include "../../include/utils.h"
#include "../../include/server.h"

void parse_port(server_t *server, char **av, int len)
{
    char *raw_port = av[1];

    if (len <= 1)
        usage("Port not specified");
    if (!is_number(raw_port))
        usage("Port is not a valid number");
    PARAMETERS->port = atoi(raw_port);
}

void parse_width(server_t *server, char **av, int len)
{
    char *raw_width = av[1];

    if (len <= 1)
        usage("Width not specified");
    if (!is_number(raw_width))
        usage("Width is not a valid number");
    PARAMETERS->width = atoi(raw_width);
}

void parse_height(server_t *server, char **av, int len)
{
    char *raw_height = av[1];

    if (len <= 1)
        usage("Height not specified");
    if (!is_number(raw_height))
        usage("Height is not a valid number");
    PARAMETERS->height = atoi(raw_height);
}

void parse_nb_clients(server_t *server, char **av, int len)
{
    char *raw_nb_clients = av[1];

    if (len <= 1)
        usage("Number of clients not specified");
    if (!is_number(raw_nb_clients))
        usage("Number of clients is not a valid number");
    PARAMETERS->nb_clients = atoi(raw_nb_clients);
}

void parse_freq(server_t *server, char **av, int len)
{
    char *raw_freq = av[1];

    if (len <= 1)
        usage("Freq is not specified");
    if (!is_number(raw_freq))
        usage("Freq is not a valid number");
    PARAMETERS->freq = atoi(raw_freq);
}
