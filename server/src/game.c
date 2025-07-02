/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/src/game.c
*/

#include "../include/server.h"
#include "../include/commands.h"

static void shread_with_teeth(server_t *server, client_t *client, size_t index)
{
    send_message(client->fd, "dead\n");
    command_pdi(server, client);
    remove_player_tile(server, client, client->position);
    remove_client(server, index);
}

static void player_eat(server_t *server, client_t *client, size_t index)
{
    if (client->inventory[FOOD] == 0)
        return shread_with_teeth(server, client, index);
    --client->inventory[FOOD];
    server_pin(server, client);
}

static void eat(server_t *server)
{
    uint64_t tick = 0;

    if (server->cons == 1)
        return;
    for (size_t i = server->cons - 2; true; --i) {
        if (!server->clients[i]->is_ai && i == 0)
            break;
        if (!server->clients[i]->is_ai)
            continue;
        tick = server->ticks - server->clients[i]->entry_tick;
        if (tick != 0 && tick % 300 == 0)
            player_eat(server, server->clients[i], i + 1);
        if (i == 0)
            break;
    }
}

static void clean_buffers(server_t *server)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        server->clients[i]->buffer = clean_buffer(server->clients[i]->buffer);
    }
}

void game_logic(server_t *server)
{
    uint64_t now = get_time_milliseconds();

    if (now < server->tick_timer)
        return;
    if (server->ticks % 20 == 0)
        handle_ressource(server);
    if (server->ticks % 500 == 0)
        clean_buffers(server);
    if (server->ticks % (PARAMETERS->freq * 10) == 0)
        server_mct(server);
    ++server->ticks;
    server->tick_timer = get_time_milliseconds() + (1000 / server->parameters->freq);
    if (!server || !server->clients)
        return;
    eat(server);
}

static bool team_won(server_t *server, char *team)
{
    for (size_t i = 0; i < server->cons - 1; ++i) {
        if (!server->clients[i]->is_ai)
            continue;
        if (strcmp(server->clients[i]->team, team) == 0 &&
            server->clients[i]->level == 8)
            return true;
    }
    return false;
}

bool is_game_done(server_t *server)
{
    for (uint16_t i = 0; i < PARAMETERS->team_count; ++i) {
        if (team_won(server, PARAMETERS->team_names[i])) {
            command_seg(server, PARAMETERS->team_names[i]);
            return true;
        }
    }
    return false;
}
