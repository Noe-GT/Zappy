/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands.c
*/

#include <string.h>
#include <poll.h>

#include "../include/commands.h"
#include "../include/game.h"

const command_t gui_commands[] = {
    { "msz\n", command_msz, 0 },
    { "bct", command_bct, 0 },
    { "mct\n", command_mct, 0 },
    { "tna\n", command_tna, 0 },
    { "ppo", command_ppo, 0 },
    { "plv", command_plv, 0 },
    { "pin", command_pin, 0 },
    { "sgt\n", command_sgt, 0 },
    { "sst", command_sst, 0 },
};

const command_t ai_commands[] = {
    { "Right\n", command_right, 7 },
    { "Left\n", command_left, 7 },
    { "Forward\n", command_forward, 7 },
    { "Look\n", command_look, 7 },
    { "Inventory\n", command_inventory, 1 },
    { "Broadcast", command_broadcast, 7 },
    { "Connect_nbr", command_broadcast, 0 },
    { "Eject", command_eject, 7 },
    { "Fork\n", command_fork, 42 },
    { "Incantation\n", command_incantation, 300 },
    { "Take", command_take, 7 },
    { "Set", command_set, 7 },
};

void find_gui_command(command_t *command, char *message)
{
    for (size_t i = 0; i < sizeof(gui_commands) / sizeof(command_t); ++i) {
        if (strncmp(message, gui_commands[i].name,
            strlen(gui_commands[i].name)) == 0) {
            memcpy(command, &gui_commands[i], sizeof(command_t));
            return;
        }
    }
    memset(command, 0, sizeof(command_t));
}

void find_ai_command(command_t *command, char *message)
{
    for (size_t i = 0; i < sizeof(ai_commands) / sizeof(command_t); ++i) {
        if (strncmp(message, ai_commands[i].name,
            strlen(ai_commands[i].name)) == 0) {
            memcpy(command, &ai_commands[i], sizeof(command_t));
            return;
        }
    }
    memset(command, 0, sizeof(command_t));
}

static void handle_gui_message(server_t *server, client_t *client)
{
    command_t command;

    if (client == NULL)
        return;
    printf("Handling massage: %s", client->queue->command);
    find_gui_command(&command, client->queue->command);
    if (command.name == 0) {
        client->queue = shift_queue(client->queue);
        return command_suc(client);
    }
    command.function(server, client, client->queue->command);
    client->queue = shift_queue(client->queue);
}

static void queue_ai_command(server_t *server, client_t *client,
    command_t *command, uint64_t now)
{
    if (!client->queue)
        return;
    if (strcmp(client->queue->command, "Fork\n") == 0)
        command_pfk(server, client);
    if (strcmp(client->queue->command, "Incantation\n") == 0) {
        command_pic(server, client);
        if (can_start_incantation(server, client)) {
            command->function(server, client, client->queue->command);
            command_pre_incantation(client);
        } else {
            printf("failed incantation, logic is mayb broken\n");
            command_pie(server, client, false);
            command_ko(client->fd);
            client->queue = shift_queue(client->queue);
            return;
        }
    }
    client->cooldown = now + (uint64_t)
        (((double)command->cooldown / server->parameters->freq) * 1000);
    client->queue->pending = true;
}

static void handle_ai_message(server_t *server, client_t *client, uint64_t now)
{
    command_t command;

    if (client == NULL)
        return;
    printf("Handling massage: %s", client->queue->command);
    find_ai_command(&command, client->queue->command);
    if (command.name == 0) {
        client->queue = shift_queue(client->queue);
        return command_ko(client->fd);
    }
    if (client->queue->pending || command.cooldown == 0) {
        command.function(server, client, client->queue->command);
        client->queue = shift_queue(client->queue);
    }
    if (client->queue && !client->queue->pending) {
        queue_ai_command(server, client, &command, now);
    }
}

static bool ai_connection_process(server_t *server, client_t *client)
{
    if (team_exists(server, client->queue->command)) {
        client->team = strndup(COMMAND, strlen(COMMAND) - 1);
        if (!replace_egg(server, client)) {
            command_ko(client->fd);
            return false;
        }
        client->is_ai = true;
        client->inventory[FOOD] = 10;
        client->queue = shift_queue(client->queue);
        command_aic(server, client);
        return true;
    }
    client->queue = shift_queue(client->queue);
    command_ko(client->fd);
    return true;
}

static bool connection_process(server_t *server, client_t *client)
{
    if (client->is_gui == false && client->is_ai == false) {
        if (strcmp(client->queue->command, "GRAPHIC\n") == 0) {
            client->is_gui = true;
            client->queue = shift_queue(client->queue);
            command_mct(server, client, NULL);
            return true;
        }
        return ai_connection_process(server, client);
    }
    return false;
}

void handle_client_commands(server_t *server)
{
    uint64_t now = get_time_milliseconds();

    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (now < server->clients[i]->cooldown)
            continue;
        if (server->clients[i]->queue == NULL)
            continue;
        if (connection_process(server, server->clients[i]))
            continue;
        if (server->clients[i]->is_gui)
            handle_gui_message(server, server->clients[i]);
        if (server->clients[i]->is_ai)
            handle_ai_message(server, server->clients[i], now);
    }
}
