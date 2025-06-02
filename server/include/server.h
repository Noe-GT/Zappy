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

typedef struct server_s {
    game_t *game;
    network_t *network;
    instruction_queue_t *instruction_queue;
} server_t;

server_t *init_server(void);
int server_run(server_t *server);

#endif /* !SERVER_HP_ */
