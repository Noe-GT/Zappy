/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/server.h"

void help(void)
{
    FILE *file = fopen("server/help.txt", "r");
    char data[50];

    if (file == NULL) {
        perror("The file is not opened");
        exit(0);
    }
    while (fgets(data, 50, file) != NULL)
        printf("%s", data);
    fclose(file);
}

void usage(char *message)
{
    help();
    fprintf(stderr, "%s\n", message);
    exit(84);
}

bool is_number(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] <= '9' && str[i] >= '0')
            continue;
        return false;
    }
    return true;
}

bool team_exists(server_t *server, char *team)
{
    for (uint16_t i = 0; i < server->parameters->team_count; ++i) {
        if (strncmp(server->parameters->team_names[i], team,
            strlen(team) - 1) == 0) {
            return true;
        }
    }
    return false;
}

uint16_t count_team_members(server_t *server, char *team)
{
    uint16_t count = 0;

    for (uint16_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_ai)
            continue;
        if (strcmp(server->clients[i]->team, team) == 0)
            ++count;
    }
    return count;
}
