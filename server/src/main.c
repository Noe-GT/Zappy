/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** server/main.c
*/

#include "../include/server.h"

void test()
{
	client_list_t *list = init_client_list();

	cl_display(list);

	cl_add_end(list, 3);
	cl_add_end(list, 2);
	// cl_add_end(list, 5);
	cl_display(list);

	cl_remove(list, 2);
	cl_add_end(list, 3);
	cl_display(list);
}

int main(void)
{
	test();
	// server_t *server = init_server();

	// if (server == NULL)
	// 	return 84;
	// server_run(server);
	return 0;
}
