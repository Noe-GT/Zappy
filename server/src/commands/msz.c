/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/msz.c
*/

#include "../../include/commands.h"

// TODO: add the map dimensions when the argument parsing is done
void command_msz(server_t *server, client_t *client, char *message)
{
    if (strcmp(message, "msz\n") != 0) {
        fprintf(stderr, "[MSZ] invalid map size command\n");
        return;
    }
    send_message(client->id, "msz 1 2\n");
}
