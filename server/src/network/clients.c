/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** clients
*/

#include "../../include/network.h"

clients_t *init_clients(void)
{
    clients_t *clients = malloc(sizeof(clients_t));

    clients->fds = malloc(sizeof(struct pollfd) * MAX_CLIENTS + 1);
    memset(clients->fds, 0, sizeof(*clients->fds));
    clients->n = 0;
    clients->available_ids = queue_init(MAX_CLIENTS);
    for (int id = 1; id <= MAX_CLIENTS; id++)
        queue_push(clients->available_ids, id);
    clients->client_list = init_client_list();
    return clients;
}

static char *handle_buff(char *t_buff, char *res_buff, int len)
{
    if (len == 2)
        strcpy(res_buff, t_buff);
    else
        strcat(res_buff, t_buff);
    return res_buff;
}

// REPLACE BY CIRCULAR BUFFER
static char *read_from_socket(int r_fd)
{
    size_t len = 1;
    char *res_buff = (char *)malloc(sizeof(char) * len);
    char *t_buff = (char *)malloc(sizeof(char) * 2);
    int r_out = read(r_fd, t_buff, 1);

    t_buff[1] = '\0';
    while (r_out != 0 && t_buff[0] != '\n') {
        if (t_buff[0] != '\r') {
            len++;
            res_buff = realloc(res_buff, len);
            res_buff = handle_buff(t_buff, res_buff, len);
        }
        r_out = read(r_fd, t_buff, 1);
        t_buff[1] = '\0';
    }
    free(t_buff);
    res_buff[len - 1] = '\0';
    return res_buff;
}

void client_handle(clients_t *clients, int i)
{
    client_t *client = cl_get(clients->client_list, i);

    if (client == NULL)
        return;
    if (client->read_buffer != NULL)
        free(client->read_buffer);
    client->read_buffer = read_from_socket(clients->fds[i].fd);
    printf("(client) id: %d | read_buffer: %s\n",
        client->id, client->read_buffer);
}

void client_remove(clients_t *clients, int i)
{
    close(clients->fds[i].fd);
    queue_push(clients->available_ids, i);
    cl_remove(clients->client_list, i);
}

static struct pollfd set_pollfd(int new_fd)
{
    struct pollfd pfd;

    pfd.fd = new_fd;
    pfd.events = POLLIN;
    return pfd;
}

void client_new(clients_t *clients, int main_socket_fd)
{
    struct sockaddr_in *addr;
    socklen_t addr_len;
    int new_fd;

    if (clients->n == MAX_CLIENTS) {
        perror("Max amount of clients reached");
        return;
    }
    addr = make_addr(main_socket_fd);
    addr_len = sizeof(addr);
    new_fd = accept(main_socket_fd, (struct sockaddr*)addr, &addr_len);
    if (new_fd < 0) {
        perror("Accept failed");
        free(addr);
        return;
    }
    clients->n++;
    printf("new client (id : %d | fd : %d)\n",
        queue_peek(clients->available_ids), new_fd);
    cl_add_end(clients->client_list, queue_peek(clients->available_ids));
    clients->fds[queue_pop(clients->available_ids)] = set_pollfd(new_fd);
}
