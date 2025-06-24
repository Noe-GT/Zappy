/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** server
*/

#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <poll.h>
#include <signal.h>
#include <stdlib.h>

#include "../include/server.h"
#include "../include/commands.h"

static void signhandler(int _)
{
    (void)_;
    exit(0);
}

static size_t handle_event(server_t *server, client_t *client, size_t i)
{
    if (!receive(server->clfds[i].fd, server->clients[i - 1]->buffer)) {
        remove_client(server, i);
        return -1;
    }
    client->queue = add_queue(client->queue, read_string(client->buffer));
    return 0;
}

static void network_events(server_t *server)
{
    int events = poll((struct pollfd *)server->clfds, server->cons, DOWNTIME);

    printf("clients: %lu - events: %d\n", server->cons - 1, events);
    if (events == 0)
        return;
    if (server->clfds[0].revents & POLLIN) {
        attach_clients(server);
        --events;
    }
    for (size_t i = 1; i < server->cons && events > 0; ++i) {
        if (server->clfds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
            remove_client(server, i);
            --i;
            continue;
        }
        if (server->clfds[i].revents & POLLIN) {
            i += handle_event(server, server->clients[i - 1], i);
            --events;
        }
    }
}

static void main_loop(server_t *server)
{
    while (true) {
        network_events(server);
        handle_client_commands(server);
        game_logic(server);
    }
}

static void initialize(server_t *server)
{
    server->map = (map_t *)malloc(sizeof(map_t));
    if (!server->map)
        exit(84);
    init_map(MAP, PARAMETERS->width, PARAMETERS->height);
}

void run_server(server_t *server)
{
    struct sockaddr_in servaddr = {0};

    signal(SIGINT, signhandler);
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->sockfd == -1)
        return (void)perror(strerror(errno));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(server->parameters->port);
    if ((bind(server->sockfd, (struct sockaddr *)&servaddr,
        sizeof(servaddr))) != 0)
        return (void)perror("Bind failed");
    if ((listen(server->sockfd, 5)) != 0)
        return (void)perror("Listen failed");
    server->clfds = malloc(sizeof(struct pollfd));
    server->clfds[0] = (struct pollfd){.fd = server->sockfd, .events = POLLIN};
    server->cons = 1;
    initialize(server);
    main_loop(server);
}
