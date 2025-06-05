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

    #include <stdbool.h>

    #define PARAMETERS server->parameters

typedef struct required_flags_s {
    bool port;
    bool width;
    bool height;
    bool teams;
    bool clients;
    bool freq;
} required_flags_t;

typedef struct parameters_s {
    uint16_t port;
    uint16_t width;
    uint16_t height;
    uint16_t nb_clients;
    uint16_t freq;
    uint16_t match_duration;
    char **team_names;
    uint16_t team_count;
    bool auto_start;
    bool display_egg;
    bool verbose;
    required_flags_t *required;
} parameters_t;

typedef struct server_s {
    parameters_t *parameters;
    game_t *game;
    network_t *network;
    instruction_queue_t *instruction_queue;
} server_t;

server_t *init_server(int max_clients);
void free_server(server_t *server);
int server_run(server_t *server);

// My parser shit
void parser(int ac, char **av, server_t *server);
void parse_port(server_t *server, char **av, int len);
void parse_width(server_t *server, char **av, int len);
void parse_height(server_t *server, char **av, int len);
void parse_nb_clients(server_t *server, char **av, int len);
void parse_freq(server_t *server, char **av, int len);
void parse_auto_start(server_t *server, char **av, int len);
void parse_display_egg(server_t *server, char **av, int len);
void parse_match_duration(server_t *server, char **av, int len);

#endif /* !SERVER_HP_ */
