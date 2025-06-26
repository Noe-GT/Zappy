/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/look.c
*/

#include "../../include/commands.h"

void command_look(server_t *server, client_t *client, char *message)
{
    printf("client %u %u\n", client->position->x, client->position->y);
    char *vision = handle_vision(server, client);

    (void)message;
    printf("this is my question %lu\n", MAP->tiles[client->position->y][client->position->x].player_count);
    printf("%s\n", vision);
    send_message(client->fd, "%s\n", vision);
    free(vision);
}
