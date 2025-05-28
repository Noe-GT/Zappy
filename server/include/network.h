/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** network
*/

#ifndef NETWORK_H_
    #define NETWORK_H_
    #include "external.h"

typedef struct client_s {
    size_t id;
} client_t;

typedef struct network_s {
    client_t *clients;
} network_t;

#endif /* !NETWORK_H_ */
