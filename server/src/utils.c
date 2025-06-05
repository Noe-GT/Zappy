/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
