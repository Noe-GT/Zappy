/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_
    #include "server.h"

    #include <string.h>
    #include <stdbool.h>

    #define COMMAND client->queue->command
    #define TILE MAP->tiles[client->position->y][client->position->x]

typedef struct command_s {
    char *name;
    void (*function)(server_t *, client_t *, char *);
    uint32_t cooldown;
} command_t;

void handle_client_commands(server_t *server);

// GUI COMMANDS
void command_msz(server_t *server, client_t *client, char *message);
void command_bct(server_t *server, client_t *client, char *message);
void command_mct(server_t *server, client_t *client, char *message);
void command_tna(server_t *server, client_t *client, char *message);
void command_ppo(server_t *server, client_t *client, char *message);
void command_pin(server_t *server, client_t *client, char *message);
void command_plv(server_t *server, client_t *client, char *message);
void command_sgt(server_t *server, client_t *client, char *message);
void command_sst(server_t *server, client_t *client, char *message);

void command_pnw(server_t *server, client_t *client);
void command_pex(client_t *client);
void command_pbc(client_t *client, const char *fmt, ...);
void command_pic(server_t *server, client_t *client);
void command_pie(server_t *server, client_t *client, bool success);
void command_pfk(server_t *server, client_t *client);
void command_pdr(server_t *server, client_t *client, int resid);
void command_pdi(server_t *server, client_t *client);
void command_enw(server_t *server, client_t *client, egg_t *egg);
void command_ebo(client_t *client, uint32_t egg_number);
void command_edi(client_t *client, uint32_t egg_number);
void command_seg(server_t *server, char *team);
void command_smg(client_t *client, const char *fmt, ...);
void command_suc(client_t *client);
void command_sbp(client_t *client);
void command_pgt(server_t *server, client_t *client, int resid);

// AI COMMANDS
void command_left(server_t *server, client_t *client, char *message);
void command_right(server_t *server, client_t *client, char *message);
void command_forward(server_t *server, client_t *client, char *message);
void command_look(server_t *server, client_t *client, char *message);
void command_inventory(server_t *server, client_t *client, char *message);
void command_broadcast(server_t *server, client_t *client, char *message);
void command_nbr(server_t *server, client_t *client, char *message);
void command_eject(server_t *server, client_t *client, char *message);
void command_fork(server_t *server, client_t *client, char *message);
void command_incantation(server_t *server, client_t *client, char *message);
void command_take(server_t *server, client_t *client, char *message);
void command_set(server_t *server, client_t *client, char *message);

// SERVER
void command_ok(int fd);
void command_ko(int fd);
void command_aic(server_t *server, client_t *client);

void bct(server_t *server, client_t *client, uint32_t x, uint32_t y);
bool can_start_incantation(server_t *server, client_t *client);

#endif /* !COMMANDS_H_ */
