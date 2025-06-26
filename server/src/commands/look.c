/*
** EPITECH PROJECT, 2025
** B-YEP-400-LYN-4-1-zappy-charly.palliere
** File description:
** server/src/commands/look.c
*/

#include "../../include/commands.h"

void command_look(server_t *server, client_t *client, char *message)
{
    char *vision = handle_vision(server, client);

    (void)message;
    printf("%s\n", vision);
    send_message(client->fd, "%s\n", vision);
    free(vision);
}
