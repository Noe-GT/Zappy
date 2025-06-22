/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands.c
*/

#include <string.h>
#include <poll.h>

#include "../include/commands.h"

const command_t client_commands[] = {
    { "msz", command_msz },
    { "bct", command_bct },
    { "mct", command_mct },
    { "tna", command_tna },
    { "ppo", command_ppo },
    { "plv", command_plv },
    { "pin", command_pin },
    { "sgt", command_sgt },
    { "sst", command_sst },
};

static void handle_message(server_t *server, client_t *client, char *message)
{
    if (client == NULL)
        return;
    printf("Handling massage: %s", message);
    for (size_t i = 0; i < sizeof(client_commands) / sizeof(command_t); ++i) {
        if (strncmp(message, client_commands[i].name,
            strlen(client_commands[i].name)) == 0) {
            client_commands[i].function(server, client, message);
        }
    }
}

void handle_client_commands(server_t *server)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (server->clients[i]->message == NULL)
            continue;
        handle_message(server, server->clients[i],
            server->clients[i]->message);
        free(server->clients[i]->message);
        server->clients[i]->message = NULL;
    }
}
