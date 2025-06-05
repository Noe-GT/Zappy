/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** commands.h
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_
    #include "network.h"
    #include "server.h"

typedef struct command_s {
    char *name;
    void (*function)(server_t *, client_t *, char *);
} command_t;

void handle_client_commands(network_t *net);

// COMMANDS
void command_msz(server_t *server, client_t *client, char *message);
void command_bct(server_t *server, client_t *client, char *message);
void command_mct(server_t *server, client_t *client, char *message);
void command_tna(server_t *server, client_t *client, char *message);
void command_ppo(server_t *server, client_t *client, char *message);
void message_pin(server_t *server, client_t *client, char *message);
void command_sgt(server_t *server, client_t *client, char *message);
void command_sst(server_t *server, client_t *client, char *message);

#endif /* !COMMANDS_H_ */
