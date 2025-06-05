/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#ifndef SERVER_HP_
    #define SERVER_HP_
    #include "game.h"
    #include "network.h"
    #include "instruction_queue.h"
    #define CLIENTS_MAX 1000

typedef struct server_s {
    game_t *game;
    network_t *network;
    instruction_queue_t *instruction_queue;
} server_t;

server_t *init_server();
void free_server(server_t *server);
void server_run(server_t *server);

#endif /* !SERVER_HP_ */
