/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#ifndef SERVER_HP_
    #define SERVER_HP_

    #include "game.h"
    #include "client.h"

    #include <stdbool.h>
    #include <stdint.h>

    #define PARAMETERS server->parameters
    #define DOWNTIME calculate_downtime(server)

typedef struct required_flags_s {
    bool port;
    bool width;
    bool height;
    bool teams;
    bool clients;
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
    int32_t sockfd;
    struct pollfd *clfds;
    uint64_t cons;
    uint64_t tick_timer;
    uint64_t ticks;
    uint64_t player_count;
    client_t **clients;
    egg_t *egg;
    uint64_t egg_count;
    map_t *map;
    bool end;
} server_t;

void run_server(server_t *server);

void attach_clients(server_t *server);
void remove_client(server_t *server, size_t index);
void init_player(server_t *server, client_t *client);

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

// Game
void game_logic(server_t *server);
void init_map(map_t *map, size_t width, size_t height);
void free_map(map_t *map);
void handle_ressource(server_t *server);
char *handle_vision(server_t *server, client_t *client);

int calculate_downtime(server_t *server);
uint64_t get_time_milliseconds(void);

bool team_exists(server_t *server, char *team);
void add_player_tile(server_t *server, client_t *client, vector2_t *position);
void remove_player_tile(server_t *server, client_t *client,
    vector2_t *position);
void forward(server_t *server, client_t *client);
void move_player(server_t *server, client_t *client, direction_t direction);

bool is_game_done(server_t *server);

#endif /* !SERVER_HP_ */
