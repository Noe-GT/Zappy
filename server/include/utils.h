/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/include/utils.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include <stdbool.h>

    #include "server.h"

// Define your utils function there
void usage(char *message);
void help(void);
bool is_number(char *str);
void out_of_bound(server_t *server, int *x, int *y);

#endif /* !UTILS_H_ */
