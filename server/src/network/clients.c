/*
** EPITECH PROJECT, 2025
** zappy - server
** File description:
** clients
*/

#include "../../include/network.h"

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

void client_handle(network_t *net, int i)
{
    client_t *client = cl_get(net->client_list, net->sockets[i].fd);

    if (client == NULL)
        return;
    if (client->read_buffer != NULL)
        free(client->read_buffer);
    client->read_buffer = read_from_socket(net->sockets[i].fd);
    printf("(client) id: %d | read_buffer: %s\n",
        client->id, client->read_buffer);
}

void client_remove(network_t *net, int i)
{
    cl_remove(net->client_list, net->sockets[i].fd);
    close(net->sockets[i].fd);
    pollfd_array_remove(net->sockets, i, net->sockets_n + 1);
    net->sockets_n--;
}

void client_new(network_t *net, int main_socket_fd)
{
    struct sockaddr_in *addr;
    socklen_t addr_len;
    int new_fd;

    if (net->sockets_n - 1 == MAX_CLIENTS) {
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
    printf("new client (fd : %d)\n", new_fd);
    cl_add_end(net->client_list, new_fd);
    net->sockets = pollfd_array_add(net->sockets, new_fd, net->sockets_n + 1);
    net->sockets_n++;
}
