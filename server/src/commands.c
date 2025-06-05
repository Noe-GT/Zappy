/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands.c
*/

#include "../include/commands.h"

const command_t client_commands[] = {
    // { "msz", temp },
    // { "bct", temp },
    // { "mct", temp },
    // { "tna", temp },
    // { "ppo", temp },
    // { "plv", temp },
    // { "pin", temp },
    // { "sgt", temp },
    // { "sst", temp },
};

static void handle_message(client_t *client)
{
    char *message;

    if (client == NULL)
        return;
    message = read_string(client->buffer);
    printf("Handling massage: %s", message);
    free(message);
}

void handle_client_commands(network_t *net)
{
    for (size_t i = 0; i < net->sockets_n + 1; ++i) {
        if (net->sockets[i].revents == POLLIN) {
            handle_message(cl_get(net->client_list, net->sockets[i].fd));
        }
    }
}
