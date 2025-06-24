/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands.c
*/

#include <string.h>
#include <poll.h>
#include <time.h>

#include "../include/commands.h"

const command_t client_commands[] = {
    { "msz", command_msz, 0 },
    { "bct", command_bct, 0 },
    { "mct", command_mct, 0 },
    { "tna", command_tna, 0 },
    { "ppo", command_ppo, 0 },
    { "plv", command_plv, 0 },
    { "pin", command_pin, 0 },
    { "sgt", command_sgt, 0 },
    { "sst", command_sst, 0 },
    { "Right\n", command_right, 1000 },
    { "Left\n", command_left, 7 },
    { "Forward\n", command_forward, 7 },
};

void find_command(command_t *command, char *message)
{
    printf("%d\n", strncmp(message, "Right\n", strlen("Right\n")));
    for (size_t i = 0; i < sizeof(client_commands) / sizeof(command_t); ++i) {
        if (strncmp(message, client_commands[i].name,
            strlen(client_commands[i].name)) == 0) {
            memcpy(command, &client_commands[i], sizeof(command_t));
            return;
        }
    }
    printf("why\n");
    memset(command, 0, sizeof(command_t));
}

static uint64_t get_time_milliseconds(void)
{
    struct timespec spec;

    clock_gettime(1, &spec);
    return spec.tv_sec * 1000 + spec.tv_nsec / 1e6;
}

static void handle_message(server_t *server, client_t *client, uint64_t now)
{
    command_t command;

    if (client == NULL)
        return;
    printf("Handling massage: %s", client->queue->command);
    find_command(&command, client->queue->command);
    if (command.name == 0)
        return command_ko(client->fd);
    if (client->queue->pending) {
        command.function(server, client, client->queue->command);
        client->queue = shift_queue(client->queue);
    } else {
        client->cooldown = now + (uint64_t)
            (((double)command.cooldown / server->parameters->freq) * 1000);
        client->queue->pending = true;
    }
}

void handle_client_commands(server_t *server)
{
    uint64_t now = get_time_milliseconds();

    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (now < server->clients[i]->cooldown)
            continue;
        if (server->clients[i]->queue == NULL)
            continue;
        handle_message(server, server->clients[i], now);
    }
}
