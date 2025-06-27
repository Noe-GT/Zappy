/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/pbc.c
*/

#include <stdarg.h>

#include "../../include/commands.h"

void command_pbc(client_t *client, const char *fmt, ...)
{
    va_list list;
    char *string = NULL;

    va_start(list, fmt);
    vasprintf(&string, fmt, list);
    va_end(list);
    send_message(client->fd, string);
    free(string);
}
