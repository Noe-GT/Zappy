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
    remove_client(server, index);
}

static void player_eat(server_t *server, client_t *client, size_t index)
{
    if (client->inventory[FOOD] == 0)
        shread_with_teeth(server, client, index);
    --client->inventory[FOOD];
}

static void eat(server_t *server)
{
    uint64_t tick = 0;
    size_t i = server->cons - 2;

    if (server->cons == 1)
        return;
    do {
        if (!server->clients[i]->is_ai)
            continue;
        tick = server->ticks - server->clients[i]->entry_tick;
        if (tick != 0 && tick % 126 == 0) {
            player_eat(server, server->clients[i], i + 1);
        }
    } while (i != 0);
}

void game_logic(server_t *server)
{
    uint64_t now = get_time_milliseconds();

    if (now < server->tick_timer)
        return;
    if (server->ticks % 20 == 0)
        handle_ressource(server);
    ++server->ticks;
    server->tick_timer = now + (1000 / server->parameters->freq);
    if (!server || !server->clients)
        return;
    eat(server);
}
