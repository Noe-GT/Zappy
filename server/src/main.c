/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/main.c
*/

#include "../include/server.h"

int main(void)
{
	server_t *server = init_server();

	if (server == NULL)
		return 84;
	server_run(server);
	return 0;
}
